#include "process_info.h"

// option -a
void print_all_procs_info(char *filename)
{
    FILE *stream = open_file_to_write_if_requested(filename);
    struct dirent *ptr_proc_dirent = NULL;
    DIR *ptr_proc_dir = opendir_and_verify(PROC_PATH);

    while ((ptr_proc_dirent = readdir(ptr_proc_dir)) != NULL)
    {
        if (is_string_a_number(ptr_proc_dirent->d_name))
        {
            char *proc_subpath = create_path_from_2_strings(PROC_PATH, ptr_proc_dirent->d_name);
            struct dirent *ptr_proc_subdirent = NULL;
            DIR *ptr_proc_subdir = opendir_and_verify(proc_subpath);

            while ((ptr_proc_subdirent = readdir(ptr_proc_subdir)) != NULL)
            {
                if (!strcmp(ptr_proc_subdirent->d_name, PROC_NAME_FILENAME))
                {
                    char *comm_path = create_path_from_2_strings(proc_subpath, PROC_NAME_FILENAME);
                    unsigned str_length = get_file_content_length(comm_path);
                    char *comm_content = get_file_content(comm_path, str_length);
                    fprintf(stream, "%s %s\n", comm_content, ptr_proc_dirent->d_name);

                    free(comm_content);
                    free(comm_path);
                    break;
                }
            }
            closedir(ptr_proc_subdir);
            free(proc_subpath);
        }
    }

    closedir(ptr_proc_dir);
    close_file_if_not_stdout(stream);
}

// option -u
void print_proc_name_from_pid(char *pid, char *filename)
{
    FILE *stream = open_file_to_write_if_requested(filename);
    struct dirent *ptr_proc_dirent = NULL;
    DIR *ptr_proc_dir = opendir_and_verify(PROC_PATH);
    bool proc_found = false;

    while ((ptr_proc_dirent = readdir(ptr_proc_dir)) != NULL && !proc_found)
    {
        if (is_string_a_number(ptr_proc_dirent->d_name) && !strcmp(ptr_proc_dirent->d_name, pid))
        {
            char *proc_subpath = create_path_from_2_strings(PROC_PATH, ptr_proc_dirent->d_name);
            struct dirent *ptr_proc_subdirent = NULL;
            DIR *ptr_proc_subdir = opendir_and_verify(proc_subpath);

            while ((ptr_proc_subdirent = readdir(ptr_proc_subdir)) != NULL && !proc_found)
            {
                if (!strcmp(ptr_proc_subdirent->d_name, PROC_NAME_FILENAME))
                {
                    char *comm_path = create_path_from_2_strings(proc_subpath, PROC_NAME_FILENAME);
                    unsigned str_length = get_file_content_length(comm_path);
                    char *comm_content = get_file_content(comm_path, str_length);

                    fprintf(stream, "%s\n", comm_content);
                    proc_found = true;

                    free(comm_content);
                    free(comm_path);
                    break;
                }
            }
            closedir(ptr_proc_subdir);
            free(proc_subpath);
        }
    }

    if (!proc_found)
    {
        fprintf(stream, "not found: No process with given PID found: %s.\n", pid);
    }

    closedir(ptr_proc_dir);
    close_file_if_not_stdout(stream);
}

// option -n
void print_proc_pid_from_name(char *process_name, char *filename)
{
    FILE *stream = open_file_to_write_if_requested(filename);
    struct dirent *ptr_proc_dirent = NULL;
    DIR *ptr_proc_dir = opendir_and_verify(PROC_PATH);
    bool proc_found = false;
    
    while ((ptr_proc_dirent = readdir(ptr_proc_dir)) != NULL)
    {
        if (is_string_a_number(ptr_proc_dirent->d_name))
        {
            char *proc_subpath = create_path_from_2_strings(PROC_PATH, ptr_proc_dirent->d_name);
            struct dirent *ptr_proc_subdirent = NULL;
            DIR *ptr_proc_subdir = opendir_and_verify(proc_subpath);
            
            while ((ptr_proc_subdirent = readdir(ptr_proc_subdir)) != NULL)
            {
                if (!strcmp(ptr_proc_subdirent->d_name, PROC_NAME_FILENAME))
                {
                    char *comm_path = create_path_from_2_strings(proc_subpath, PROC_NAME_FILENAME);
                    unsigned str_length = get_file_content_length(comm_path);
                    char *comm_content = get_file_content(comm_path, str_length);

                    if (!strcmp(comm_content, process_name))
                    {
                        proc_found = true;
                        fprintf(stream, "%s ", ptr_proc_dirent->d_name);
                    }
                    
                    free(comm_content);
                    free(comm_path);
                    break;
                }
            }
            closedir(ptr_proc_subdir);
            free(proc_subpath);
        }
    }

    if (proc_found)
    {
        fprintf(stream, "\n");
    }
    else
    {
        fprintf(stream, "not found: No process with given name found: %s.\n", process_name);
    }

    closedir(ptr_proc_dir);
    close_file_if_not_stdout(stream);
}