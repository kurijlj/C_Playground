/* ==========================================================================
 *  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of <PROGRAM_NAME>.
 *
 * <PROGRAM_NAME> is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * <PROGRAM_NAME> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with Focus Precision Analyze. If not, see <https://www.gnu.org/licenses/>.
 * ========================================================================== */


/* ==========================================================================
 *
 * 2023-09-09 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * status_reporting.h: created.
 *
 * ========================================================================== */


#ifndef STATUS_REPORTING_H
#define STATUS_REPORTING_H

/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Standard Library headers */
#include <stdio.h>
#include <time.h>


/* ==========================================================================
 * Macros definitions section
 * ========================================================================== */

#define SR_TIME_STAMP_BUFFER_SIZE 20
#define SR_EXECUTION              0
#define SR_ERROR                  1
#define SR_WARNING                2


/* --------------------------------------------------------------------------
 * Function: show_status(int staus_type, const char* message, const char*
 *                  caller, const char* app_name)
 * --------------------------------------------------------------------------
 * 
 * Description: Prints a status message to the standard output stream or
 *              standard error stream. The message is prefixed with a time
 *              stamp and a status type. The status type can be one of the
 *              following:
 *                  - SR_EXECUTION: The message is a general status message.
 *                  - SR_ERROR: The message is an error message.
 *                  - SR_WARNING: The message is a warning message.
 * 
 *              The time stamp is in the format "yyyy-mm-dd hh:mm:ss".
 * 
 *              The general format of the message is as follows:
 *                  TIME_STAMP> [APP_NAME: ][STATUS_TYPE][ in CALLER][: ]MESSAGE
 * 
 *              Depending on the status type, the message is printed to the
 *              standard output stream or standard error stream. Messages of
 *              type SR_ERROR and SR_WARNING are printed to the standard error
 *              stream, while messages of type SR_EXECUTION are printed to the
 *              standard output stream.
 * 
 *              This function is intended to be used by other library
 *              functions to report status messages to the user. So it is not
 *              recommended to use this function directly. Instead, use one of
 *              the following functions:
 *                  - execution_status()
 *                  - error_status()
 *                  - warning_status()
 * 
 * Parameters:
 *            - staus_type: The type of the status message. Can be one of
 *                          the following:
 *                              - SR_EXECUTION: The message is a general
 *                                              status message.
 *                              - SR_ERROR:     The message is an error message.
 *                              - SR_WARNING:   The message is a warning
 *                                              message.
 *               - message: The status message to be printed.
 *                - caller: The name of the function that called this function.
 *                          Can be NULL.
 *              - app_name: The name of the application that called
 *                          this function.
 * 
 * Returns:     The number of characters printed to the standard output stream
 *              or standard error stream. If an error occurs, a negative value
 *              is returned.
 * 
 * -------------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------------
 * Function: execution_status(const char* message, const char* caller,
 *                  const char* app_name)
 * --------------------------------------------------------------------------
 * 
 * Description: Prints a status message to the standard output stream. The
 *              message is prefixed with a time stamp.
 * 
 *              The time stamp is in the format "yyyy-mm-dd hh:mm:ss".
 * 
 *              The general format of the message is as follows:
 *                  TIME_STAMP> [APP_NAME: ][ in CALLER][: ]MESSAGE
 * 
 * Parameters:
 *               - message: The status message to be printed.
 *                - caller: The name of the function that called this function.
 *                          Can be NULL.
 *              - app_name: The name of the application that called
 *                          this function.
 * 
 * Returns:     The number of characters printed to the standard output stream
 *              or standard error stream. If an error occurs, a negative value
 *              is returned.
 * 
 * -------------------------------------------------------------------------- */
int execution_status(const char* message, const char* caller,
        const char* app_name) {
    return show_status(SR_EXECUTION, message, caller, app_name);

}

/* --------------------------------------------------------------------------
 * Function: error_status(const char* message, const char* caller,
 *                  const char* app_name)
 * --------------------------------------------------------------------------
 * 
 * Description: Prints an error message to the standard error stream. The
 *              message is prefixed with a time stamp.
 * 
 *              The time stamp is in the format "yyyy-mm-dd hh:mm:ss".
 * 
 *              The general format of the message is as follows:
 *                  TIME_STAMP> [APP_NAME: ]ERROR[ in CALLER][: ]MESSAGE
 * 
 * Parameters:
 *               - message: The status message to be printed.
 *                - caller: The name of the function that called this function.
 *                          Can be NULL.
 *              - app_name: The name of the application that called
 *                          this function.
 * 
 * Returns:     The number of characters printed to the standard output stream
 *              or standard error stream. If an error occurs, a negative value
 *              is returned.
 * 
 * -------------------------------------------------------------------------- */
int error_status(const char* message, const char* caller,
        const char* app_name) {
    return show_status(SR_ERROR, message, caller, app_name);

}

/* --------------------------------------------------------------------------
 * Function: warning_status(const char* message, const char* caller,
 *                  const char* app_name)
 * --------------------------------------------------------------------------
 * 
 * Description: Prints an warning message to the standard error stream. The
 *              message is prefixed with a time stamp.
 * 
 *              The time stamp is in the format "yyyy-mm-dd hh:mm:ss".
 * 
 *              The general format of the message is as follows:
 *                  TIME_STAMP> [APP_NAME: ]WARNING[ in CALLER][: ]MESSAGE
 * 
 * Parameters:
 *               - message: The status message to be printed.
 *                - caller: The name of the function that called this function.
 *                          Can be NULL.
 *              - app_name: The name of the application that called
 *                          this function.
 * 
 * Returns:     The number of characters printed to the standard output stream
 *              or standard error stream. If an error occurs, a negative value
 *              is returned.
 * 
 * -------------------------------------------------------------------------- */
int warning_status(const char* message, const char* caller,
        const char* app_name) {
    return show_status(SR_WARNING, message, caller, app_name);

}

#endif // STATUS_REPORTING_H