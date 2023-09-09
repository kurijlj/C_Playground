#ifndef STATUS_REPORTING_H
#define STATUS_REPORTING_H

#define SR_TIME_STAMP_BUFFER_SIZE 20
#define SR_EXECUTION              0
#define SR_ERROR                  1
#define SR_WARNING                2

#include <stdio.h>
#include <time.h>

int show_status(int staus_type, const char* message, const char* caller,
        const char* app_name) {
    char time_stamp[SR_TIME_STAMP_BUFFER_SIZE] = "yyyy-mm-dd hh:mm:ss";
    time_t t = time(NULL);
    int status = 0;
    FILE *out = stdout;

    /* Determine the output stream */
    if (SR_ERROR == staus_type || SR_WARNING == staus_type) {
        out = stderr;
    
    }

    strftime(
             time_stamp,
             SR_TIME_STAMP_BUFFER_SIZE,
             "%Y-%m-%d %H:%M:%S",
             localtime(&t)
            );
    
    if (NULL == caller && NULL == app_name) {
        if (SR_ERROR == staus_type) {
            status = fprintf(
                    out,
                    "%s> ERROR: %s\n",
                    time_stamp,
                    message
                );

        } else if (SR_WARNING == staus_type) {
            status = fprintf(
                    out,
                    "%s> WARNING: %s\n",
                    time_stamp,
                    message
                );

        } else {
            status = fprintf(
                    out,
                    "%s> %s\n",
                    time_stamp,
                    message
                );

        }

    } else if (NULL != caller && NULL == app_name) {
        if (SR_ERROR == staus_type) {
            status = fprintf(
                    out,
                    "%s> ERROR in '%s': %s\n",
                    time_stamp,
                    caller,
                    message
                );

        } else if (SR_WARNING == staus_type) {
            status = fprintf(
                    out,
                    "%s> WARNING in '%s': %s\n",
                    time_stamp,
                    caller,
                    message
                );

        } else {
            status = fprintf(
                    out,
                    "%s> in '%s': %s\n",
                    time_stamp,
                    caller,
                    message
                );

        }

    } else if (NULL == caller && NULL != app_name) {
        if (SR_ERROR == staus_type) {
            status = fprintf(
                    out,
                    "%s> %s: ERROR: %s\n",
                    time_stamp,
                    app_name,
                    message
                );

        } else if (SR_WARNING == staus_type) {
            status = fprintf(
                    out,
                    "%s> %s: WARNING: %s\n",
                    time_stamp,
                    app_name,
                    message
                );

        } else {
            status = fprintf(
                    out,
                    "%s> %s: %s\n",
                    time_stamp,
                    app_name,
                    message
                );

        }

    } else {
        if (SR_ERROR == staus_type) {
            status = fprintf(
                    out,
                    "%s> %s: ERROR in '%s': %s\n",
                    time_stamp,
                    app_name,
                    caller,
                    message
                );

        } else if (SR_WARNING == staus_type) {
            status = fprintf(
                    out,
                    "%s> %s: WARNING in '%s': %s\n",
                    time_stamp,
                    app_name,
                    caller,
                    message
                );

        } else {
            status = fprintf(
                    out,
                    "%s> %s: in '%s': %s\n",
                    time_stamp,
                    app_name,
                    caller,
                    message
                );

        }


    }

    return status;

}

int execution_status(const char* message, const char* caller,
        const char* app_name) {
    return show_status(SR_EXECUTION, message, caller, app_name);

}

int error_status(const char* message, const char* caller,
        const char* app_name) {
    return show_status(SR_ERROR, message, caller, app_name);

}

int warning_status(const char* message, const char* caller,
        const char* app_name) {
    return show_status(SR_WARNING, message, caller, app_name);

}

#endif // STATUS_REPORTING_H