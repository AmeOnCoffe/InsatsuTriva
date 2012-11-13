/*
 * "$Id$"
 *
 *   Internet Printing Protocol definitions for CUPS.
 *
 *   Copyright 2007-2012 by Apple Inc.
 *   Copyright 1997-2006 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_IPP_H_
#  define _CUPS_IPP_H_

/*
 * Include necessary headers...
 */

#  include "http.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * IPP version string...
 */

#  define IPP_VERSION		"\002\001"

/*
 * IPP registered port number...
 *
 * Note: Applications should never use IPP_PORT, but instead use the
 * ippPort() function to allow overrides via the IPP_PORT environment
 * variable and services file if needed!
 */

#  define IPP_PORT		631

/*
 * Common limits...
 */

#  define IPP_MAX_CHARSET	64	/* Maximum length of charset values w/nul */
#  define IPP_MAX_KEYWORD	256	/* Maximum length of keyword values w/nul */
#  define IPP_MAX_LANGUAGE	64	/* Maximum length of naturalLanguage values w/nul */
#  define IPP_MAX_LENGTH	32767	/* Maximum size of any single value */
#  define IPP_MAX_MIMETYPE	256	/* Maximum length of mimeMediaType values w/nul */
#  define IPP_MAX_NAME		256	/* Maximum length of common name values w/nul */
#  define IPP_MAX_OCTETSTRING	1023	/* Maximum length of octetString values w/o nul */
#  define IPP_MAX_TEXT		1024	/* Maximum length of text values w/nul */
#  define IPP_MAX_URI		1024	/* Maximum length of uri values w/nul */
#  define IPP_MAX_URISCHEME	64	/* Maximum length of uriScheme values w/nul */
#  define IPP_MAX_VALUES	8	/* Power-of-2 allocation increment */


/*
 * Types and structures...
 */

typedef enum ipp_dstate_e		/**** Document states ****/
{
  IPP_DOCUMENT_PENDING = 3,		/* Document is pending */
  IPP_DOCUMENT_PROCESSING = 5,		/* Document is processing */
  IPP_DOCUMENT_CANCELED = 7,		/* Document is canceled */
  IPP_DOCUMENT_ABORTED,			/* Document is aborted */
  IPP_DOCUMENT_COMPLETED		/* Document is completed */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_DOCUMENT_PENDING	IPP_DSTATE_PENDING
#    define IPP_DOCUMENT_PROCESSING	IPP_DSTATE_PROCESSING
#    define IPP_DOCUMENT_CANCELED	IPP_DSTATE_CANCELED
#    define IPP_DOCUMENT_ABORTED	IPP_DSTATE_ABORTED
#    define IPP_DOCUMENT_COMPLETED	IPP_DSTATE_COMPLETED
#  endif /* !_CUPS_NO_DEPRECATED */
} ipp_dstate_t;

typedef enum ipp_finishings_e		/**** Finishings ****/
{
  IPP_FINISHINGS_NONE = 3,		/* No finishing */
  IPP_FINISHINGS_STAPLE,		/* Staple (any location) */
  IPP_FINISHINGS_PUNCH,			/* Punch (any location/count) */
  IPP_FINISHINGS_COVER,			/* Add cover */
  IPP_FINISHINGS_BIND,			/* Bind */
  IPP_FINISHINGS_SADDLE_STITCH,		/* Staple interior */
  IPP_FINISHINGS_EDGE_STITCH,		/* Stitch along any side */
  IPP_FINISHINGS_FOLD,			/* Fold (any type) */
  IPP_FINISHINGS_TRIM,			/* Trim (any type) */
  IPP_FINISHINGS_BALE,			/* Bale (any type) */
  IPP_FINISHINGS_BOOKLET_MAKER,		/* Fold to make booklet */
  IPP_FINISHINGS_JOB_OFFSET,		/* Offset for binding (any type) */
  IPP_FINISHINGS_STAPLE_TOP_LEFT = 20,	/* Staple top left corner */
  IPP_FINISHINGS_STAPLE_BOTTOM_LEFT,	/* Staple bottom left corner */
  IPP_FINISHINGS_STAPLE_TOP_RIGHT,	/* Staple top right corner */
  IPP_FINISHINGS_STAPLE_BOTTOM_RIGHT,	/* Staple bottom right corner */
  IPP_FINISHINGS_EDGE_STITCH_LEFT,	/* Stitch along left side */
  IPP_FINISHINGS_EDGE_STITCH_TOP,	/* Stitch along top edge */
  IPP_FINISHINGS_EDGE_STITCH_RIGHT,	/* Stitch along right side */
  IPP_FINISHINGS_EDGE_STITCH_BOTTOM,	/* Stitch along bottom edge */
  IPP_FINISHINGS_STAPLE_DUAL_LEFT,	/* Two staples on left */
  IPP_FINISHINGS_STAPLE_DUAL_TOP,	/* Two staples on top */
  IPP_FINISHINGS_STAPLE_DUAL_RIGHT,	/* Two staples on right */
  IPP_FINISHINGS_STAPLE_DUAL_BOTTOM,	/* Two staples on bottom */
  IPP_FINISHINGS_BIND_LEFT = 50,	/* Bind on left */
  IPP_FINISHINGS_BIND_TOP,		/* Bind on top */
  IPP_FINISHINGS_BIND_RIGHT,		/* Bind on right */
  IPP_FINISHINGS_BIND_BOTTOM,		/* Bind on bottom */
  IPP_FINISHINGS_TRIM_AFTER_PAGES = 60,	/* Trim output after each page */
  IPP_FINISHINGS_TRIM_AFTER_DOCUMENTS,	/* Trim output after each document */
  IPP_FINISHINGS_TRIM_AFTER_COPIES,	/* Trim output after each copy */
  IPP_FINISHINGS_TRIM_AFTER_JOB,	/* Trim output after job */

  /* Proposed extensions for finishings */
  IPP_FINISHINGS_CUPS_PUNCH_TOP_LEFT = 0x40000046,
					/* Punch 1 hole top left */
  IPP_FINISHINGS_CUPS_PUNCH_BOTTOM_LEFT,/* Punch 1 hole bottom left */
  IPP_FINISHINGS_CUPS_PUNCH_TOP_RIGHT,	/* Punch 1 hole top right */
  IPP_FINISHINGS_CUPS_PUNCH_BOTTOM_RIGHT,
					/* Punch 1 hole bottom right */
  IPP_FINISHINGS_CUPS_PUNCH_DUAL_LEFT,	/* Punch 2 holes left side */
  IPP_FINISHINGS_CUPS_PUNCH_DUAL_TOP,	/* Punch 2 holes top edge */
  IPP_FINISHINGS_CUPS_PUNCH_DUAL_RIGHT,	/* Punch 2 holes right side */
  IPP_FINISHINGS_CUPS_PUNCH_DUAL_BOTTOM,/* Punch 2 holes bottom edge */
  IPP_FINISHINGS_CUPS_PUNCH_TRIPLE_LEFT,/* Punch 3 holes left side */
  IPP_FINISHINGS_CUPS_PUNCH_TRIPLE_TOP,	/* Punch 3 holes top edge */
  IPP_FINISHINGS_CUPS_PUNCH_TRIPLE_RIGHT,
					/* Punch 3 holes right side */
  IPP_FINISHINGS_CUPS_PUNCH_TRIPLE_BOTTOM,
					/* Punch 3 holes bottom edge */
  IPP_FINISHINGS_CUPS_PUNCH_QUAD_LEFT,	/* Punch 4 holes left side */
  IPP_FINISHINGS_CUPS_PUNCH_QUAD_TOP,	/* Punch 4 holes top edge */
  IPP_FINISHINGS_CUPS_PUNCH_QUAD_RIGHT,	/* Punch 4 holes right side */
  IPP_FINISHINGS_CUPS_PUNCH_QUAD_BOTTOM	/* Punch 4 holes bottom edge */
} ipp_finishings_t;
#  ifndef _CUPS_NO_DEPRECATED
typedef enum ipp_finishings_e ipp_finish_t;
#  endif /* !_CUPS_NO_DEPRECATED */

typedef enum ipp_jcollate_e		/**** Job collation types ****/
{
  IPP_JCOLLATE_UNCOLLATED_SHEETS = 3,
  IPP_JCOLLATE_COLLATED_DOCUMENTS,
  IPP_JCOLLATE_UNCOLLATED_DOCUMENTS

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_JOB_UNCOLLATED_SHEETS		IPP_JCOLLATE_UNCOLLATED_SHEETS
#    define IPP_JOB_COLLATED_DOCUMENTS		IPP_JCOLLATE_COLLATED_DOCUMENTS
#    define IPP_JOB_UNCOLLATED_DOCUMENTS	IPP_JCOLLATE_UNCOLLATED_DOCUMENTS
#  endif /* !_CUPS_NO_DEPRECATED */
} ipp_jcollate_t;

typedef enum ipp_jstate_e		/**** Job states ****/
{
  IPP_JSTATE_PENDING = 3,		/* Job is waiting to be printed */
  IPP_JSTATE_HELD,			/* Job is held for printing */
  IPP_JSTATE_PROCESSING,		/* Job is currently printing */
  IPP_JSTATE_STOPPED,			/* Job has been stopped */
  IPP_JSTATE_CANCELED,			/* Job has been canceled */
  IPP_JSTATE_ABORTED,			/* Job has aborted due to error */
  IPP_JSTATE_COMPLETED			/* Job has completed successfully */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_JOB_PENDING	IPP_JSTATE_PENDING
#    define IPP_JOB_HELD	IPP_JSTATE_HELD
#    define IPP_JOB_PROCESSING	IPP_JSTATE_PROCESSING
#    define IPP_JOB_STOPPED	IPP_JSTATE_STOPPED
#    define IPP_JOB_CANCELED	IPP_JSTATE_CANCELED
#    define IPP_JOB_ABORTED	IPP_JSTATE_ABORTED
#    define IPP_JOB_COMPLETED	IPP_JSTATE_COMPLETED
  /* Legacy name for canceled state */
#    define IPP_JOB_CANCELLED	IPP_JSTATE_CANCELED
#  endif /* !_CUPS_NO_DEPRECATED */
} ipp_jstate_t;

typedef enum ipp_op_e			/**** IPP operations ****/
{
  IPP_OP_CUPS_INVALID = -1,		/* Invalid operation name for @link ippOpValue@ */
  IPP_OP_CUPS_NONE = 0,			/* No operation @private@ */
  IPP_OP_PRINT_JOB = 0x0002,		/* Print a single file */
  IPP_OP_PRINT_URI,			/* Print a single URL @private@ */
  IPP_OP_VALIDATE_JOB,			/* Validate job options */
  IPP_OP_CREATE_JOB,			/* Create an empty print job */
  IPP_OP_SEND_DOCUMENT,			/* Add a file to a job */
  IPP_OP_SEND_URI,			/* Add a URL to a job @private@ */
  IPP_OP_CANCEL_JOB,			/* Cancel a job */
  IPP_OP_GET_JOB_ATTRIBUTES,		/* Get job attributes */
  IPP_OP_GET_JOBS,			/* Get a list of jobs */
  IPP_OP_GET_PRINTER_ATTRIBUTES,	/* Get printer attributes */
  IPP_OP_HOLD_JOB,			/* Hold a job for printing */
  IPP_OP_RELEASE_JOB,			/* Release a job for printing */
  IPP_OP_RESTART_JOB,			/* Reprint a job */
  IPP_OP_PAUSE_PRINTER = 0x0010,	/* Stop a printer */
  IPP_OP_RESUME_PRINTER,		/* Start a printer */
  IPP_OP_PURGE_JOBS,			/* Cancel all jobs */
  IPP_OP_SET_PRINTER_ATTRIBUTES,	/* Set printer attributes @private@ */
  IPP_OP_SET_JOB_ATTRIBUTES,		/* Set job attributes */
  IPP_OP_GET_PRINTER_SUPPORTED_VALUES,	/* Get supported attribute values */
  IPP_OP_CREATE_PRINTER_SUBSCRIPTION,	/* Create a printer subscription @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_CREATE_JOB_SUBSCRIPTION,	/* Create a job subscription @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_GET_SUBSCRIPTION_ATTRIBUTES,	/* Get subscription attributes @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_GET_SUBSCRIPTIONS,		/* Get list of subscriptions @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_RENEW_SUBSCRIPTION,		/* Renew a printer subscription @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_CANCEL_SUBSCRIPTION,		/* Cancel a subscription @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_GET_NOTIFICATIONS,		/* Get notification events @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_SEND_NOTIFICATIONS,		/* Send notification events @private@ */
  IPP_OP_GET_RESOURCE_ATTRIBUTES,	/* Get resource attributes @private@ */
  IPP_OP_GET_RESOURCE_DATA,		/* Get resource data @private@ */
  IPP_OP_GET_RESOURCES,			/* Get list of resources @private@ */
  IPP_OP_GET_PRINT_SUPPORT_FILES,	/* Get printer support files @private@ */
  IPP_OP_ENABLE_PRINTER,		/* Start a printer */
  IPP_OP_DISABLE_PRINTER,		/* Stop a printer */
  IPP_OP_PAUSE_PRINTER_AFTER_CURRENT_JOB,
					/* Stop printer after the current job @private@ */
  IPP_OP_HOLD_NEW_JOBS,			/* Hold new jobs @private@ */
  IPP_OP_RELEASE_HELD_NEW_JOBS,		/* Release new jobs @private@ */
  IPP_OP_DEACTIVATE_PRINTER,		/* Stop a printer @private@ */
  IPP_OP_ACTIVATE_PRINTER,		/* Start a printer @private@ */
  IPP_OP_RESTART_PRINTER,		/* Restart a printer @private@ */
  IPP_OP_SHUTDOWN_PRINTER,		/* Turn a printer off @private@ */
  IPP_OP_STARTUP_PRINTER,		/* Turn a printer on @private@ */
  IPP_OP_REPROCESS_JOB,			/* Reprint a job @private@ */
  IPP_OP_CANCEL_CURRENT_JOB,		/* Cancel the current job @private@ */
  IPP_OP_SUSPEND_CURRENT_JOB,		/* Suspend the current job @private@ */
  IPP_OP_RESUME_JOB,			/* Resume the current job @private@ */
  IPP_OP_PROMOTE_JOB,			/* Promote a job to print sooner @private@ */
  IPP_OP_SCHEDULE_JOB_AFTER,		/* Schedule a job to print after another @private@ */
  IPP_OP_CANCEL_DOCUMENT = 0x0033,	/* Cancel-Document @private@ */
  IPP_OP_GET_DOCUMENT_ATTRIBUTES,	/* Get-Document-Attributes @private@ */
  IPP_OP_GET_DOCUMENTS,			/* Get-Documents @private@ */
  IPP_OP_DELETE_DOCUMENT,		/* Delete-Document @private@ */
  IPP_OP_SET_DOCUMENT_ATTRIBUTES,	/* Set-Document-Attributes @private@ */
  IPP_OP_CANCEL_JOBS,			/* Cancel-Jobs */
  IPP_OP_CANCEL_MY_JOBS,		/* Cancel-My-Jobs */
  IPP_OP_RESUBMIT_JOB,			/* Resubmit-Job */
  IPP_OP_CLOSE_JOB,			/* Close-Job */
  IPP_OP_IDENTIFY_PRINTER,		/* Identify-Printer (proposed IPP JPS3) */
  IPP_OP_VALIDATE_DOCUMENT,		/* Validate-Document (proposed IPP JPS3) */
  IPP_OP_PRIVATE = 0x4000,		/* Reserved @private@ */
  IPP_OP_CUPS_GET_DEFAULT,		/* Get the default printer */
  IPP_OP_CUPS_GET_PRINTERS,		/* Get a list of printers and/or classes */
  IPP_OP_CUPS_ADD_MODIFY_PRINTER,	/* Add or modify a printer */
  IPP_OP_CUPS_DELETE_PRINTER,		/* Delete a printer */
  IPP_OP_CUPS_GET_CLASSES,		/* Get a list of classes @deprecated@ */
  IPP_OP_CUPS_ADD_MODIFY_CLASS,		/* Add or modify a class */
  IPP_OP_CUPS_DELETE_CLASS,		/* Delete a class */
  IPP_OP_CUPS_ACCEPT_JOBS,		/* Accept new jobs on a printer */
  IPP_OP_CUPS_REJECT_JOBS,		/* Reject new jobs on a printer */
  IPP_OP_CUPS_SET_DEFAULT,		/* Set the default printer */
  IPP_OP_CUPS_GET_DEVICES,		/* Get a list of supported devices */
  IPP_OP_CUPS_GET_PPDS,			/* Get a list of supported drivers */
  IPP_OP_CUPS_MOVE_JOB,			/* Move a job to a different printer */
  IPP_OP_CUPS_AUTHENTICATE_JOB,		/* Authenticate a job @since CUPS 1.2/OS X 10.5@ */
  IPP_OP_CUPS_GET_PPD,			/* Get a PPD file @since CUPS 1.3/OS X 10.5@ */
  IPP_OP_CUPS_GET_DOCUMENT = 0x4027	/* Get a document file @since CUPS 1.4/OS X 10.6@ */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_PRINT_JOB			IPP_OP_PRINT_JOB
#    define IPP_PRINT_URI			IPP_OP_PRINT_URI
#    define IPP_VALIDATE_JOB			IPP_OP_VALIDATE_JOB
#    define IPP_CREATE_JOB			IPP_OP_CREATE_JOB
#    define IPP_SEND_DOCUMENT			IPP_OP_SEND_DOCUMENT
#    define IPP_SEND_URI			IPP_OP_SEND_URI
#    define IPP_CANCEL_JOB			IPP_OP_CANCEL_JOB
#    define IPP_GET_JOB_ATTRIBUTES		IPP_OP_GET_JOB_ATTRIBUTES
#    define IPP_GET_JOBS			IPP_OP_GET_JOBS
#    define IPP_GET_PRINTER_ATTRIBUTES		IPP_OP_GET_PRINTER_ATTRIBUTES
#    define IPP_HOLD_JOB			IPP_OP_HOLD_JOB
#    define IPP_RELEASE_JOB			IPP_OP_RELEASE_JOB
#    define IPP_RESTART_JOB			IPP_OP_RESTART_JOB
#    define IPP_PAUSE_PRINTER			IPP_OP_PAUSE_PRINTER
#    define IPP_RESUME_PRINTER			IPP_OP_RESUME_PRINTER
#    define IPP_PURGE_JOBS			IPP_OP_PURGE_JOBS
#    define IPP_SET_PRINTER_ATTRIBUTES		IPP_OP_SET_PRINTER_ATTRIBUTES
#    define IPP_SET_JOB_ATTRIBUTES		IPP_OP_SET_JOB_ATTRIBUTES
#    define IPP_GET_PRINTER_SUPPORTED_VALUES	IPP_OP_GET_PRINTER_SUPPORTED_VALUES
#    define IPP_CREATE_PRINTER_SUBSCRIPTION	IPP_OP_CREATE_PRINTER_SUBSCRIPTION
#    define IPP_CREATE_JOB_SUBSCRIPTION		IPP_OP_CREATE_JOB_SUBSCRIPTION
#    define IPP_GET_SUBSCRIPTION_ATTRIBUTES	IPP_OP_GET_SUBSCRIPTION_ATTRIBUTES
#    define IPP_GET_SUBSCRIPTIONS		IPP_OP_GET_SUBSCRIPTIONS
#    define IPP_RENEW_SUBSCRIPTION		IPP_OP_RENEW_SUBSCRIPTION
#    define IPP_CANCEL_SUBSCRIPTION		IPP_OP_CANCEL_SUBSCRIPTION
#    define IPP_GET_NOTIFICATIONS		IPP_OP_GET_NOTIFICATIONS
#    define IPP_SEND_NOTIFICATIONS		IPP_OP_SEND_NOTIFICATIONS
#    define IPP_GET_RESOURCE_ATTRIBUTES		IPP_OP_GET_RESOURCE_ATTRIBUTES
#    define IPP_GET_RESOURCE_DATA		IPP_OP_GET_RESOURCE_DATA
#    define IPP_GET_RESOURCES			IPP_OP_GET_RESOURCES
#    define IPP_GET_PRINT_SUPPORT_FILES		IPP_OP_GET_PRINT_SUPPORT_FILES
#    define IPP_ENABLE_PRINTER			IPP_OP_ENABLE_PRINTER
#    define IPP_DISABLE_PRINTER			IPP_OP_DISABLE_PRINTER
#    define IPP_PAUSE_PRINTER_AFTER_CURRENT_JOB	IPP_OP_PAUSE_PRINTER_AFTER_CURRENT_JOB
#    define IPP_HOLD_NEW_JOBS			IPP_OP_HOLD_NEW_JOBS
#    define IPP_RELEASE_HELD_NEW_JOBS		IPP_OP_RELEASE_HELD_NEW_JOBS
#    define IPP_DEACTIVATE_PRINTER		IPP_OP_DEACTIVATE_PRINTER
#    define IPP_ACTIVATE_PRINTER		IPP_OP_ACTIVATE_PRINTER
#    define IPP_RESTART_PRINTER			IPP_OP_RESTART_PRINTER
#    define IPP_SHUTDOWN_PRINTER		IPP_OP_SHUTDOWN_PRINTER
#    define IPP_STARTUP_PRINTER			IPP_OP_STARTUP_PRINTER
#    define IPP_REPROCESS_JOB			IPP_OP_REPROCESS_JOB
#    define IPP_CANCEL_CURRENT_JOB		IPP_OP_CANCEL_CURRENT_JOB
#    define IPP_SUSPEND_CURRENT_JOB		IPP_OP_SUSPEND_CURRENT_JOB
#    define IPP_RESUME_JOB			IPP_OP_RESUME_JOB
#    define IPP_PROMOTE_JOB			IPP_OP_PROMOTE_JOB
#    define IPP_SCHEDULE_JOB_AFTER		IPP_OP_SCHEDULE_JOB_AFTER
#    define IPP_CANCEL_DOCUMENT			IPP_OP_CANCEL_DOCUMENT
#    define IPP_GET_DOCUMENT_ATTRIBUTES		IPP_OP_GET_DOCUMENT_ATTRIBUTES
#    define IPP_GET_DOCUMENTS			IPP_OP_GET_DOCUMENTS
#    define IPP_DELETE_DOCUMENT			IPP_OP_DELETE_DOCUMENT
#    define IPP_SET_DOCUMENT_ATTRIBUTES		IPP_OP_SET_DOCUMENT_ATTRIBUTES
#    define IPP_CANCEL_JOBS			IPP_OP_CANCEL_JOBS
#    define IPP_CANCEL_MY_JOBS			IPP_OP_CANCEL_MY_JOBS
#    define IPP_RESUBMIT_JOB			IPP_OP_RESUBMIT_JOB
#    define IPP_CLOSE_JOB			IPP_OP_CLOSE_JOB
#    define IPP_IDENTIFY_PRINTER		IPP_OP_IDENTIFY_PRINTER
#    define IPP_VALIDATE_DOCUMENT		IPP_OP_VALIDATE_DOCUMENT
#    define IPP_PRIVATE				IPP_OP_PRIVATE
#    define CUPS_GET_DEFAULT			IPP_OP_CUPS_GET_DEFAULT
#    define CUPS_GET_PRINTERS			IPP_OP_CUPS_GET_PRINTERS
#    define CUPS_ADD_MODIFY_PRINTER		IPP_OP_CUPS_ADD_MODIFY_PRINTER
#    define CUPS_DELETE_PRINTER			IPP_OP_CUPS_DELETE_PRINTER
#    define CUPS_GET_CLASSES			IPP_OP_CUPS_GET_CLASSES
#    define CUPS_ADD_MODIFY_CLASS		IPP_OP_CUPS_ADD_MODIFY_CLASS
#    define CUPS_DELETE_CLASS			IPP_OP_CUPS_DELETE_CLASS
#    define CUPS_ACCEPT_JOBS			IPP_OP_CUPS_ACCEPT_JOBS
#    define CUPS_REJECT_JOBS			IPP_OP_CUPS_REJECT_JOBS
#    define CUPS_SET_DEFAULT			IPP_OP_CUPS_SET_DEFAULT
#    define CUPS_GET_DEVICES			IPP_OP_CUPS_GET_DEVICES
#    define CUPS_GET_PPDS			IPP_OP_CUPS_GET_PPDS
#    define CUPS_MOVE_JOB			IPP_OP_CUPS_MOVE_JOB
#    define CUPS_AUTHENTICATE_JOB		IPP_OP_CUPS_AUTHENTICATE_JOB
#    define CUPS_GET_PPD			IPP_OP_CUPS_GET_PPD
#    define CUPS_GET_DOCUMENT			IPP_OP_CUPS_GET_DOCUMENT
     /* Legacy names */
#    define CUPS_ADD_PRINTER			IPP_OP_CUPS_ADD_MODIFY_PRINTER
#    define CUPS_ADD_CLASS			IPP_OP_CUPS_ADD_MODIFY_CLASS
#  endif /* !_CUPS_NO_DEPRECATED */
} ipp_op_t;

typedef enum ipp_orient_e		/**** Orientation values ****/
{
  IPP_ORIENT_PORTRAIT = 3,		/* No rotation */
  IPP_ORIENT_LANDSCAPE,			/* 90 degrees counter-clockwise */
  IPP_ORIENT_REVERSE_LANDSCAPE,		/* 90 degrees clockwise */
  IPP_ORIENT_REVERSE_PORTRAIT		/* 180 degrees */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_PORTRAIT		IPP_ORIENT_PORTRAIT
#    define IPP_LANDSCAPE		IPP_ORIENT_LANDSCAPE
#    define IPP_REVERSE_LANDSCAPE	IPP_ORIENT_REVERSE_LANDSCAPE
#    define IPP_REVERSE_PORTRAIT	IPP_ORIENT_REVERSE_PORTRAIT
#  endif /* !_CUPS_NO_DEPRECATED */
} ipp_orient_t;

typedef enum ipp_pstate_e		/**** Printer states ****/
{
  IPP_PSTATE_IDLE = 3,			/* Printer is idle */
  IPP_PSTATE_PROCESSING,		/* Printer is working */
  IPP_PSTATE_STOPPED			/* Printer is stopped */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_PRINTER_IDLE		IPP_PSTATE_IDLE
#    define IPP_PRINTER_PROCESSING	IPP_PSTATE_PROCESSING
#    define IPP_PRINTER_STOPPED		IPP_PSTATE_STOPPED
#  endif /* _CUPS_NO_DEPRECATED */
} ipp_pstate_t;

typedef enum ipp_quality_e		/**** Qualities ****/
{
  IPP_QUALITY_DRAFT = 3,		/* Draft quality */
  IPP_QUALITY_NORMAL,			/* Normal quality */
  IPP_QUALITY_HIGH			/* High quality */
} ipp_quality_t;

typedef enum ipp_res_e			/**** Resolution units ****/
{
  IPP_RES_PER_INCH = 3,			/* Pixels per inch */
  IPP_RES_PER_CM			/* Pixels per centimeter */
} ipp_res_t;

typedef enum ipp_state_e		/**** IPP states ****/
{
  IPP_STATE_ERROR = -1,			/* An error occurred */
  IPP_STATE_IDLE,			/* Nothing is happening/request completed */
  IPP_STATE_HEADER,			/* The request header needs to be sent/received */
  IPP_STATE_ATTRIBUTE,			/* One or more attributes need to be sent/received */
  IPP_STATE_DATA			/* IPP request data needs to be sent/received */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_ERROR		IPP_STATE_ERROR
#    define IPP_IDLE		IPP_STATE_IDLE
#    define IPP_HEADER		IPP_STATE_HEADER
#    define IPP_ATTRIBUTE	IPP_STATE_ATTRIBUTE
#    define IPP_DATA		IPP_STATE_DATA
#  endif /* !_CUPS_NO_DEPRECATED */
} ipp_state_t;

typedef enum ipp_status_e		/**** IPP status codes ****/
{
  IPP_STATUS_CUPS_INVALID = -1,		/* Invalid status name for @link ippErrorValue@ */
  IPP_STATUS_OK = 0x0000,		/* successful-ok */
  IPP_STATUS_OK_IGNORED_OR_SUBSTITUTED,	/* successful-ok-ignored-or-substituted-attributes */
  IPP_STATUS_OK_CONFLICTING,		/* successful-ok-conflicting-attributes */
  IPP_STATUS_OK_IGNORED_SUBSCRIPTIONS,	/* successful-ok-ignored-subscriptions */
  IPP_STATUS_OK_IGNORED_NOTIFICATIONS,	/* successful-ok-ignored-notifications @private@ */
  IPP_STATUS_OK_TOO_MANY_EVENTS,	/* successful-ok-too-many-events */
  IPP_STATUS_OK_BUT_CANCEL_SUBSCRIPTION,/* successful-ok-but-cancel-subscription @private@ */
  IPP_STATUS_OK_EVENTS_COMPLETE,	/* successful-ok-events-complete */
  IPP_STATUS_REDIRECTION_OTHER_SITE = 0x0200,
					/* redirection-other-site @private@ */
  IPP_STATUS_CUPS_SEE_OTHER = 0x0280,	/* cups-see-other */
  IPP_STATUS_ERROR_BAD_REQUEST = 0x0400,/* client-error-bad-request */
  IPP_STATUS_ERROR_FORBIDDEN,		/* client-error-forbidden */
  IPP_STATUS_ERROR_NOT_AUTHENTICATED,	/* client-error-not-authenticated */
  IPP_STATUS_ERROR_NOT_AUTHORIZED,	/* client-error-not-authorized */
  IPP_STATUS_ERROR_NOT_POSSIBLE,	/* client-error-not-possible */
  IPP_STATUS_ERROR_TIMEOUT,		/* client-error-timeout */
  IPP_STATUS_ERROR_NOT_FOUND,		/* client-error-not-found */
  IPP_STATUS_ERROR_GONE,		/* client-error-gone */
  IPP_STATUS_ERROR_REQUEST_ENTITY,	/* client-error-request-entity-too-large */
  IPP_STATUS_ERROR_REQUEST_VALUE,	/* client-error-request-value-too-long */
  IPP_STATUS_ERROR_DOCUMENT_FORMAT_NOT_SUPPORTED,
					/* client-error-document-format-not-supported */
  IPP_STATUS_ERROR_ATTRIBUTES_OR_VALUES,/* client-error-attributes-or-values-not-supported */
  IPP_STATUS_ERROR_URI_SCHEME,		/* client-error-uri-scheme-not-supported */
  IPP_STATUS_ERROR_CHARSET,		/* client-error-charset-not-supported */
  IPP_STATUS_ERROR_CONFLICTING,		/* client-error-conflicting-attributes */
  IPP_STATUS_ERROR_COMPRESSION_NOT_SUPPORTED,
					/* client-error-compression-not-supported */
  IPP_STATUS_ERROR_COMPRESSION_ERROR,	/* client-error-compression-error */
  IPP_STATUS_ERROR_DOCUMENT_FORMAT_ERROR,
					/* client-error-document-format-error */
  IPP_STATUS_ERROR_DOCUMENT_ACCESS,	/* client-error-document-access-error */
  IPP_STATUS_ERROR_ATTRIBUTES_NOT_SETTABLE,
					/* client-error-attributes-not-settable */
  IPP_STATUS_ERROR_IGNORED_ALL_SUBSCRIPTIONS,
					/* client-error-ignored-all-subscriptions */
  IPP_STATUS_ERROR_TOO_MANY_SUBSCRIPTIONS,
					/* client-error-too-many-subscriptions */
  IPP_STATUS_ERROR_IGNORED_ALL_NOTIFICATIONS,
					/* client-error-ignored-all-notifications @private@ */
  IPP_STATUS_ERROR_PRINT_SUPPORT_FILE_NOT_FOUND,
					/* client-error-print-support-file-not-found @private@ */
  IPP_STATUS_ERROR_DOCUMENT_PASSWORD,	/* client-error-document-password-error */
  IPP_STATUS_ERROR_DOCUMENT_PERMISSION,	/* client-error-document-permission-error */
  IPP_STATUS_ERROR_DOCUMENT_SECURITY,	/* client-error-document-security-error */
  IPP_STATUS_ERROR_DOCUMENT_UNPRINTABLE,/* client-error-document-unprintable-error */

  /* Proposed extensions for paid printing */
  IPP_STATUS_ERROR_CUPS_ACCOUNT_INFO_NEEDED = 0x049C,
					/* cups-error-account-info-needed @since CUPS 1.7@ */
  IPP_STATUS_ERROR_CUPS_ACCOUNT_CLOSED,	/* cups-error-account-closed @since CUPS 1.7@ */
  IPP_STATUS_ERROR_CUPS_ACCOUNT_LIMIT_REACHED,
					/* cups-error-account-limit-reached @since CUPS 1.7@ */
  IPP_STATUS_ERROR_CUPS_ACCOUNT_AUTHORIZATION_FAILED,
					/* cups-error-account-authorization-failed @since CUPS 1.7@ */

  IPP_STATUS_ERROR_INTERNAL = 0x0500,	/* server-error-internal-error */
  IPP_STATUS_ERROR_OPERATION_NOT_SUPPORTED,
					/* server-error-operation-not-supported */
  IPP_STATUS_ERROR_SERVICE_UNAVAILABLE,	/* server-error-service-unavailable */
  IPP_STATUS_ERROR_VERSION_NOT_SUPPORTED,
					/* server-error-version-not-supported */
  IPP_STATUS_ERROR_DEVICE,		/* server-error-device-error */
  IPP_STATUS_ERROR_TEMPORARY,		/* server-error-temporary-error */
  IPP_STATUS_ERROR_NOT_ACCEPTING_JOBS,	/* server-error-not-accepting-jobs */
  IPP_STATUS_ERROR_BUSY,		/* server-error-busy */
  IPP_STATUS_ERROR_JOB_CANCELED,	/* server-error-job-canceled */
  IPP_STATUS_ERROR_MULTIPLE_JOBS_NOT_SUPPORTED,
					/* server-error-multiple-document-jobs-not-supported */
  IPP_STATUS_ERROR_PRINTER_IS_DEACTIVATED,
					/* server-error-printer-is-deactivated */
  IPP_STATUS_ERROR_TOO_MANY_JOBS,	/* server-error-too-many-jobs */
  IPP_STATUS_ERROR_TOO_MANY_DOCUMENTS,	/* server-error-too-many-documents */

  /* These are internal and never sent over the wire... */
  IPP_STATUS_ERROR_CUPS_AUTHENTICATION_CANCELED = 0x1000,
					/* cups-authentication-canceled - Authentication canceled by user @since CUPS 1.5/OS X 10.7@ */
  IPP_STATUS_ERROR_CUPS_PKI,		/* cups-pki-error - Error negotiating a secure connection @since CUPS 1.5/OS X 10.7@ */
  IPP_STATUS_ERROR_CUPS_UPGRADE_REQUIRED/* cups-upgrade-required - TLS upgrade required */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_OK				IPP_STATUS_OK
#    define IPP_OK_SUBST			IPP_STATUS_OK_IGNORED_OR_SUBSTITUTED
#    define IPP_OK_CONFLICT			IPP_STATUS_OK_CONFLICTING
#    define IPP_OK_IGNORED_SUBSCRIPTIONS	IPP_STATUS_OK_IGNORED_SUBSCRIPTIONS
#    define IPP_OK_IGNORED_NOTIFICATIONS	IPP_STATUS_OK_IGNORED_NOTIFICATIONS
#    define IPP_OK_TOO_MANY_EVENTS		IPP_STATUS_OK_TOO_MANY_EVENTS
#    define IPP_OK_BUT_CANCEL_SUBSCRIPTION	IPP_STATUS_OK_BUT_CANCEL_SUBSCRIPTION
#    define IPP_OK_EVENTS_COMPLETE		IPP_STATUS_OK_EVENTS_COMPLETE
#    define IPP_REDIRECTION_OTHER_SITE		IPP_STATUS_REDIRECTION_OTHER_SITE
#    define CUPS_SEE_OTHER			IPP_STATUS_CUPS_SEE_OTHER
#    define IPP_BAD_REQUEST			IPP_STATUS_ERROR_BAD_REQUEST
#    define IPP_FORBIDDEN			IPP_STATUS_ERROR_FORBIDDEN
#    define IPP_NOT_AUTHENTICATED		IPP_STATUS_ERROR_NOT_AUTHENTICATED
#    define IPP_NOT_AUTHORIZED			IPP_STATUS_ERROR_NOT_AUTHORIZED
#    define IPP_NOT_POSSIBLE			IPP_STATUS_ERROR_NOT_POSSIBLE
#    define IPP_TIMEOUT				IPP_STATUS_ERROR_TIMEOUT
#    define IPP_NOT_FOUND			IPP_STATUS_ERROR_NOT_FOUND
#    define IPP_GONE				IPP_STATUS_ERROR_GONE
#    define IPP_REQUEST_ENTITY			IPP_STATUS_ERROR_REQUEST_ENTITY
#    define IPP_REQUEST_VALUE			IPP_STATUS_ERROR_REQUEST_VALUE
#    define IPP_DOCUMENT_FORMAT			IPP_STATUS_ERROR_DOCUMENT_FORMAT_NOT_SUPPORTED
#    define IPP_ATTRIBUTES			IPP_STATUS_ERROR_ATTRIBUTES_OR_VALUES
#    define IPP_URI_SCHEME			IPP_STATUS_ERROR_URI_SCHEME
#    define IPP_CHARSET				IPP_STATUS_ERROR_CHARSET
#    define IPP_CONFLICT			IPP_STATUS_ERROR_CONFLICTING
#    define IPP_COMPRESSION_NOT_SUPPORTED	IPP_STATUS_ERROR_COMPRESSION_NOT_SUPPORTED
#    define IPP_COMPRESSION_ERROR		IPP_STATUS_ERROR_COMPRESSION_ERROR
#    define IPP_DOCUMENT_FORMAT_ERROR		IPP_STATUS_ERROR_DOCUMENT_FORMAT_ERROR
#    define IPP_DOCUMENT_ACCESS_ERROR		IPP_STATUS_ERROR_DOCUMENT_ACCESS
#    define IPP_ATTRIBUTES_NOT_SETTABLE		IPP_STATUS_ERROR_ATTRIBUTES_NOT_SETTABLE
#    define IPP_IGNORED_ALL_SUBSCRIPTIONS	IPP_STATUS_ERROR_IGNORED_ALL_SUBSCRIPTIONS
#    define IPP_TOO_MANY_SUBSCRIPTIONS		IPP_STATUS_ERROR_TOO_MANY_SUBSCRIPTIONS
#    define IPP_IGNORED_ALL_NOTIFICATIONS	IPP_STATUS_ERROR_IGNORED_ALL_NOTIFICATIONS
#    define IPP_PRINT_SUPPORT_FILE_NOT_FOUND	IPP_STATUS_ERROR_PRINT_SUPPORT_FILE_NOT_FOUND
#    define IPP_DOCUMENT_PASSWORD_ERROR		IPP_STATUS_ERROR_DOCUMENT_PASSWORD
#    define IPP_DOCUMENT_PERMISSION_ERROR	IPP_STATUS_ERROR_DOCUMENT_PERMISSION
#    define IPP_DOCUMENT_SECURITY_ERROR		IPP_STATUS_ERROR_DOCUMENT_SECURITY
#    define IPP_DOCUMENT_UNPRINTABLE_ERROR	IPP_STATUS_ERROR_DOCUMENT_UNPRINTABLE
#    define IPP_INTERNAL_ERROR			IPP_STATUS_ERROR_INTERNAL
#    define IPP_OPERATION_NOT_SUPPORTED		IPP_STATUS_ERROR_OPERATION_NOT_SUPPORTED
#    define IPP_SERVICE_UNAVAILABLE		IPP_STATUS_ERROR_SERVICE_UNAVAILABLE
#    define IPP_VERSION_NOT_SUPPORTED		IPP_STATUS_ERROR_VERSION_NOT_SUPPORTED
#    define IPP_DEVICE_ERROR			IPP_STATUS_ERROR_DEVICE
#    define IPP_TEMPORARY_ERROR			IPP_STATUS_ERROR_TEMPORARY
#    define IPP_NOT_ACCEPTING			IPP_STATUS_ERROR_NOT_ACCEPTING_JOBS
#    define IPP_PRINTER_BUSY			IPP_STATUS_ERROR_BUSY
#    define IPP_ERROR_JOB_CANCELED		IPP_STATUS_ERROR_JOB_CANCELED
#    define IPP_MULTIPLE_JOBS_NOT_SUPPORTED	IPP_STATUS_ERROR_MULTIPLE_JOBS_NOT_SUPPORTED
#    define IPP_PRINTER_IS_DEACTIVATED		IPP_STATUS_ERROR_PRINTER_IS_DEACTIVATED
#    define IPP_TOO_MANY_JOBS			IPP_STATUS_ERROR_TOO_MANY_JOBS
#    define IPP_TOO_MANY_DOCUMENTS		IPP_STATUS_ERROR_TOO_MANY_DOCUMENTS
#    define IPP_AUTHENTICATION_CANCELED		IPP_STATUS_ERROR_CUPS_AUTHENTICATION_CANCELED
#    define IPP_PKI_ERROR			IPP_STATUS_ERROR_CUPS_PKI
#    define IPP_UPGRADE_REQUIRED		IPP_STATUS_ERROR_CUPS_UPGRADE_REQUIRED
     /* Legacy name for canceled status */
#    define IPP_ERROR_JOB_CANCELLED		IPP_STATUS_ERROR_JOB_CANCELED
#  endif /* _CUPS_NO_DEPRECATED */
} ipp_status_t;

typedef enum ipp_tag_e			/**** Format tags for attributes ****/
{
  IPP_TAG_CUPS_INVALID = -1,		/* Invalid tag name for @link ippTagValue@ */
  IPP_TAG_ZERO = 0x00,			/* Zero tag - used for separators */
  IPP_TAG_OPERATION,			/* Operation group */
  IPP_TAG_JOB,				/* Job group */
  IPP_TAG_END,				/* End-of-attributes */
  IPP_TAG_PRINTER,			/* Printer group */
  IPP_TAG_UNSUPPORTED_GROUP,		/* Unsupported attributes group */
  IPP_TAG_SUBSCRIPTION,			/* Subscription group */
  IPP_TAG_EVENT_NOTIFICATION,		/* Event group */
  IPP_TAG_RESOURCE,			/* Resource group @private@ */
  IPP_TAG_DOCUMENT,			/* Document group */
  IPP_TAG_UNSUPPORTED_VALUE = 0x10,	/* Unsupported value */
  IPP_TAG_DEFAULT,			/* Default value */
  IPP_TAG_UNKNOWN,			/* Unknown value */
  IPP_TAG_NOVALUE,			/* No-value value */
  IPP_TAG_NOTSETTABLE = 0x15,		/* Not-settable value */
  IPP_TAG_DELETEATTR,			/* Delete-attribute value */
  IPP_TAG_ADMINDEFINE,			/* Admin-defined value */
  IPP_TAG_INTEGER = 0x21,		/* Integer value */
  IPP_TAG_BOOLEAN,			/* Boolean value */
  IPP_TAG_ENUM,				/* Enumeration value */
  IPP_TAG_STRING = 0x30,		/* Octet string value */
  IPP_TAG_DATE,				/* Date/time value */
  IPP_TAG_RESOLUTION,			/* Resolution value */
  IPP_TAG_RANGE,			/* Range value */
  IPP_TAG_BEGIN_COLLECTION,		/* Beginning of collection value */
  IPP_TAG_TEXTLANG,			/* Text-with-language value */
  IPP_TAG_NAMELANG,			/* Name-with-language value */
  IPP_TAG_END_COLLECTION,		/* End of collection value */
  IPP_TAG_TEXT = 0x41,			/* Text value */
  IPP_TAG_NAME,				/* Name value */
  IPP_TAG_RESERVED_STRING,		/* Reserved for future string value @private@ */
  IPP_TAG_KEYWORD,			/* Keyword value */
  IPP_TAG_URI,				/* URI value */
  IPP_TAG_URISCHEME,			/* URI scheme value */
  IPP_TAG_CHARSET,			/* Character set value */
  IPP_TAG_LANGUAGE,			/* Language value */
  IPP_TAG_MIMETYPE,			/* MIME media type value */
  IPP_TAG_MEMBERNAME,			/* Collection member name value */
  IPP_TAG_EXTENSION = 0x7f,		/* Extension point for 32-bit tags */
  IPP_TAG_CUPS_MASK = 0x7fffffff,	/* Mask for copied attribute values @private@ */
  /* The following expression is used to avoid compiler warnings with +/-0x80000000 */
  IPP_TAG_CUPS_CONST = -0x7fffffff-1	/* Bitflag for copied/const attribute values @private@ */

#  ifndef _CUPS_NO_DEPRECATED
#    define IPP_TAG_MASK		IPP_TAG_CUPS_MASK
#    define IPP_TAG_COPY		IPP_TAG_CUPS_CONST
#  endif /* !_CUPS_NO_DEPRECATED */
} ipp_tag_t;

typedef unsigned char ipp_uchar_t;	/**** Unsigned 8-bit integer/character ****/
typedef struct _ipp_s ipp_t;		/**** IPP request/response data ****/
typedef struct _ipp_attribute_s ipp_attribute_t;
					/**** IPP attribute ****/

/**** New in CUPS 1.2/OS X 10.5 ****/
typedef ssize_t	(*ipp_iocb_t)(void *context, ipp_uchar_t *buffer, size_t bytes);
					/**** IPP IO Callback Function @since CUPS 1.2/OS X 10.5@ ****/

/**** New in CUPS 1.6/OS X 10.8 ****/
typedef int (*ipp_copycb_t)(void *context, ipp_t *dst, ipp_attribute_t *attr);


/*
 * The following structures are PRIVATE starting with CUPS 1.6/OS X 10.8.
 * Please use the new accessor functions available in CUPS 1.6 and later, as
 * these definitions will be moved to a private header file in a future release.
 *
 * Define _IPP_PRIVATE_STRUCTURES to 1 to cause the private IPP structures to be
 * exposed in CUPS 1.6.  This happens automatically on OS X when compiling for
 * a deployment target of 10.7 or earlier.
 *
 * Define _IPP_PRIVATE_STRUCTURES to 0 to prevent the private IPP structures
 * from being exposed.  This is useful when migrating existing code to the new
 * accessors.
 */

#  ifdef _IPP_PRIVATE_STRUCTURES
     /* Somebody has overridden the value */
#  elif defined(_CUPS_SOURCE) || defined(_CUPS_IPP_PRIVATE_H_)
     /* Building CUPS */
#    define _IPP_PRIVATE_STRUCTURES 1
#  elif defined(__APPLE__)
#    if defined(MAC_OS_X_VERSION_10_8) && MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_8
       /* Building for 10.7 and earlier */
#      define _IPP_PRIVATE_STRUCTURES 1
#    elif !defined(MAC_OS_X_VERSION_10_8)
       /* Building for 10.7 and earlier */
#      define _IPP_PRIVATE_STRUCTURES 1
#    endif /* MAC_OS_X_VERSION_10_8 && MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_8 */
#  else
#    define _IPP_PRIVATE_STRUCTURES 0
#  endif /* _CUPS_SOURCE || _CUPS_IPP_PRIVATE_H_ */

#  if _IPP_PRIVATE_STRUCTURES
typedef union _ipp_request_u		/**** Request Header ****/
{
  struct				/* Any Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    int		op_status;		/* Operation ID or status code*/
    int		request_id;		/* Request ID */
  }		any;

  struct				/* Operation Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_op_t	operation_id;		/* Operation ID */
    int		request_id;		/* Request ID */
  }		op;

  struct				/* Status Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_status_t status_code;		/* Status code */
    int		request_id;		/* Request ID */
  }		status;

  /**** New in CUPS 1.1.19 ****/
  struct				/* Event Header @since CUPS 1.1.19/OS X 10.3@ */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_status_t status_code;		/* Status code */
    int		request_id;		/* Request ID */
  }		event;
} _ipp_request_t;

/**** New in CUPS 1.1.19 ****/

typedef union _ipp_value_u		/**** Attribute Value ****/
{
  int		integer;		/* Integer/enumerated value */

  char		boolean;		/* Boolean value */

  ipp_uchar_t	date[11];		/* Date/time value */

  struct
  {
    int		xres,			/* Horizontal resolution */
		yres;			/* Vertical resolution */
    ipp_res_t	units;			/* Resolution units */
  }		resolution;		/* Resolution value */

  struct
  {
    int		lower,			/* Lower value */
		upper;			/* Upper value */
  }		range;			/* Range of integers value */

  struct
  {
    char	*language;		/* Language code */
    char	*text;			/* String */
  }		string;			/* String with language value */

  struct
  {
    int		length;			/* Length of attribute */
    void	*data;			/* Data in attribute */
  }		unknown;		/* Unknown attribute type */

/**** New in CUPS 1.1.19 ****/
  ipp_t		*collection;		/* Collection value @since CUPS 1.1.19/OS X 10.3@ */
} _ipp_value_t;
typedef _ipp_value_t ipp_value_t;	/**** Convenience typedef that will be removed @private@ ****/

struct _ipp_attribute_s			/**** Attribute ****/
{
  ipp_attribute_t *next;		/* Next attribute in list */
  ipp_tag_t	group_tag,		/* Job/Printer/Operation group tag */
		value_tag;		/* What type of value is it? */
  char		*name;			/* Name of attribute */
  int		num_values;		/* Number of values */
  _ipp_value_t	values[1];		/* Values */
};

struct _ipp_s				/**** IPP Request/Response/Notification ****/
{
  ipp_state_t		state;		/* State of request */
  _ipp_request_t	request;	/* Request header */
  ipp_attribute_t	*attrs;		/* Attributes */
  ipp_attribute_t	*last;		/* Last attribute in list */
  ipp_attribute_t	*current;	/* Current attribute (for read/write) */
  ipp_tag_t		curtag;		/* Current attribute group tag */

/**** New in CUPS 1.2 ****/
  ipp_attribute_t	*prev;		/* Previous attribute (for read) @since CUPS 1.2/OS X 10.5@ */

/**** New in CUPS 1.4.4 ****/
  int			use;		/* Use count @since CUPS 1.4.4/OS X 10.6.?@ */
};
#  endif /* _IPP_PRIVATE_STRUCTURES */


/*
 * Prototypes...
 */

extern ipp_attribute_t	*ippAddBoolean(ipp_t *ipp, ipp_tag_t group,
			               const char *name, char value);
extern ipp_attribute_t	*ippAddBooleans(ipp_t *ipp, ipp_tag_t group,
			                const char *name, int num_values,
					const char *values);
extern ipp_attribute_t	*ippAddDate(ipp_t *ipp, ipp_tag_t group,
			            const char *name, const ipp_uchar_t *value);
extern ipp_attribute_t	*ippAddInteger(ipp_t *ipp, ipp_tag_t group,
			               ipp_tag_t value_tag, const char *name,
				       int value);
extern ipp_attribute_t	*ippAddIntegers(ipp_t *ipp, ipp_tag_t group,
			                ipp_tag_t value_tag, const char *name,
					int num_values, const int *values);
extern ipp_attribute_t	*ippAddRange(ipp_t *ipp, ipp_tag_t group,
			             const char *name, int lower, int upper);
extern ipp_attribute_t	*ippAddRanges(ipp_t *ipp, ipp_tag_t group,
			              const char *name, int num_values,
				      const int *lower, const int *upper);
extern ipp_attribute_t	*ippAddResolution(ipp_t *ipp, ipp_tag_t group,
			                  const char *name, ipp_res_t units,
					  int xres, int yres);
extern ipp_attribute_t	*ippAddResolutions(ipp_t *ipp, ipp_tag_t group,
			                   const char *name, int num_values,
					   ipp_res_t units, const int *xres,
					   const int *yres);
extern ipp_attribute_t	*ippAddSeparator(ipp_t *ipp);
extern ipp_attribute_t	*ippAddString(ipp_t *ipp, ipp_tag_t group,
			              ipp_tag_t value_tag, const char *name,
				      const char *language, const char *value);
extern ipp_attribute_t	*ippAddStrings(ipp_t *ipp, ipp_tag_t group,
			               ipp_tag_t value_tag, const char *name,
				       int num_values, const char *language,
				       const char * const *values);
extern time_t		ippDateToTime(const ipp_uchar_t *date);
extern void		ippDelete(ipp_t *ipp);
extern const char	*ippErrorString(ipp_status_t error);
extern ipp_attribute_t	*ippFindAttribute(ipp_t *ipp, const char *name,
			                  ipp_tag_t value_tag);
extern ipp_attribute_t	*ippFindNextAttribute(ipp_t *ipp, const char *name,
			                      ipp_tag_t value_tag);
extern size_t		ippLength(ipp_t *ipp);
extern ipp_t		*ippNew(void);
extern ipp_state_t	ippRead(http_t *http, ipp_t *ipp);
extern const ipp_uchar_t *ippTimeToDate(time_t t);
extern ipp_state_t	ippWrite(http_t *http, ipp_t *ipp);
extern int		ippPort(void);
extern void		ippSetPort(int p);

/**** New in CUPS 1.1.19 ****/
extern ipp_attribute_t	*ippAddCollection(ipp_t *ipp, ipp_tag_t group,
			                  const char *name, ipp_t *value) _CUPS_API_1_1_19;
extern ipp_attribute_t	*ippAddCollections(ipp_t *ipp, ipp_tag_t group,
			                   const char *name, int num_values,
					   const ipp_t **values) _CUPS_API_1_1_19;
extern void		ippDeleteAttribute(ipp_t *ipp, ipp_attribute_t *attr) _CUPS_API_1_1_19;
extern ipp_state_t	ippReadFile(int fd, ipp_t *ipp) _CUPS_API_1_1_19;
extern ipp_state_t	ippWriteFile(int fd, ipp_t *ipp) _CUPS_API_1_1_19;

/**** New in CUPS 1.2/OS X 10.5 ****/
extern ipp_attribute_t	*ippAddOctetString(ipp_t *ipp, ipp_tag_t group,
			                   const char *name,
					   const void *data, int datalen) _CUPS_API_1_2;
extern ipp_status_t	ippErrorValue(const char *name) _CUPS_API_1_2;
extern ipp_t		*ippNewRequest(ipp_op_t op) _CUPS_API_1_2;
extern const char	*ippOpString(ipp_op_t op) _CUPS_API_1_2;
extern ipp_op_t		ippOpValue(const char *name) _CUPS_API_1_2;
extern ipp_state_t	ippReadIO(void *src, ipp_iocb_t cb, int blocking,
			          ipp_t *parent, ipp_t *ipp) _CUPS_API_1_2;
extern ipp_state_t	ippWriteIO(void *dst, ipp_iocb_t cb, int blocking,
			           ipp_t *parent, ipp_t *ipp) _CUPS_API_1_2;

/**** New in CUPS 1.4/OS X 10.6 ****/
extern const char	*ippTagString(ipp_tag_t tag) _CUPS_API_1_4;
extern ipp_tag_t	ippTagValue(const char *name) _CUPS_API_1_4;

/**** New in CUPS 1.6/OS X 10.8 ****/
extern ipp_attribute_t	*ippAddOutOfBand(ipp_t *ipp, ipp_tag_t group,
			                 ipp_tag_t value_tag, const char *name)
			                 _CUPS_API_1_6;
extern size_t		ippAttributeString(ipp_attribute_t *attr, char *buffer,
			                   size_t bufsize) _CUPS_API_1_6;
extern ipp_attribute_t	*ippCopyAttribute(ipp_t *dst, ipp_attribute_t *attr,
			                 int quickcopy) _CUPS_API_1_6;
extern int		ippCopyAttributes(ipp_t *dst, ipp_t *src,
			                  int quickcopy, ipp_copycb_t cb,
			                  void *context) _CUPS_API_1_6;
extern int		ippDeleteValues(ipp_t *ipp, ipp_attribute_t **attr,
			                int element, int count) _CUPS_API_1_6;
extern const char	*ippEnumString(const char *attrname, int enumvalue)
			               _CUPS_API_1_6;
extern int		ippEnumValue(const char *attrname,
			             const char *enumstring) _CUPS_API_1_6;
extern ipp_attribute_t	*ippFirstAttribute(ipp_t *ipp) _CUPS_API_1_6;
extern int		ippGetBoolean(ipp_attribute_t *attr, int element)
			              _CUPS_API_1_6;
extern ipp_t		*ippGetCollection(ipp_attribute_t *attr,
			                  int element) _CUPS_API_1_6;
extern int		ippGetCount(ipp_attribute_t *attr) _CUPS_API_1_6;
extern const ipp_uchar_t *ippGetDate(ipp_attribute_t *attr, int element)
			             _CUPS_API_1_6;
extern ipp_tag_t	ippGetGroupTag(ipp_attribute_t *attr) _CUPS_API_1_6;
extern int		ippGetInteger(ipp_attribute_t *attr, int element)
			              _CUPS_API_1_6;
extern const char	*ippGetName(ipp_attribute_t *attr) _CUPS_API_1_6;
extern ipp_op_t		ippGetOperation(ipp_t *ipp) _CUPS_API_1_6;
extern int		ippGetRange(ipp_attribute_t *attr, int element,
			            int *upper) _CUPS_API_1_6;
extern int		ippGetRequestId(ipp_t *ipp) _CUPS_API_1_6;
extern int		ippGetResolution(ipp_attribute_t *attr, int element,
			                 int *yres, ipp_res_t *units)
			                 _CUPS_API_1_6;
extern ipp_state_t	ippGetState(ipp_t *ipp) _CUPS_API_1_6;
extern ipp_status_t	ippGetStatusCode(ipp_t *ipp) _CUPS_API_1_6;
extern const char	*ippGetString(ipp_attribute_t *attr, int element,
				      const char **language) _CUPS_API_1_6;
extern ipp_tag_t	ippGetValueTag(ipp_attribute_t *attr) _CUPS_API_1_6;
extern int		ippGetVersion(ipp_t *ipp, int *minor) _CUPS_API_1_6;
extern ipp_attribute_t	*ippNextAttribute(ipp_t *ipp) _CUPS_API_1_6;
extern int		ippSetBoolean(ipp_t *ipp, ipp_attribute_t **attr,
			              int element, int boolvalue) _CUPS_API_1_6;
extern int		ippSetCollection(ipp_t *ipp, ipp_attribute_t **attr,
			                 int element, ipp_t *colvalue)
			                 _CUPS_API_1_6;
extern int		ippSetDate(ipp_t *ipp, ipp_attribute_t **attr,
			            int element, const ipp_uchar_t *datevalue)
				    _CUPS_API_1_6;
extern int		ippSetGroupTag(ipp_t *ipp, ipp_attribute_t **attr,
			               ipp_tag_t group_tag) _CUPS_API_1_6;
extern int		ippSetInteger(ipp_t *ipp, ipp_attribute_t **attr,
			              int element, int intvalue) _CUPS_API_1_6;
extern int		ippSetName(ipp_t *ipp, ipp_attribute_t **attr,
			            const char *name) _CUPS_API_1_6;
extern int		ippSetOperation(ipp_t *ipp, ipp_op_t op) _CUPS_API_1_6;
extern int		ippSetRange(ipp_t *ipp, ipp_attribute_t **attr,
			            int element, int lowervalue, int uppervalue)
			            _CUPS_API_1_6;
extern int		ippSetRequestId(ipp_t *ipp, int request_id)
			                _CUPS_API_1_6;
extern int		ippSetResolution(ipp_t *ipp, ipp_attribute_t **attr,
			                 int element, ipp_res_t unitsvalue,
			                 int xresvalue, int yresvalue)
			                 _CUPS_API_1_6;
extern int		ippSetState(ipp_t *ipp, ipp_state_t state)
			            _CUPS_API_1_6;
extern int		ippSetStatusCode(ipp_t *ipp, ipp_status_t status)
			                 _CUPS_API_1_6;
extern int		ippSetString(ipp_t *ipp, ipp_attribute_t **attr,
			             int element, const char *strvalue)
			             _CUPS_API_1_6;
extern int		ippSetValueTag(ipp_t *ipp, ipp_attribute_t **attr,
			               ipp_tag_t value_tag) _CUPS_API_1_6;
extern int		ippSetVersion(ipp_t *ipp, int major, int minor)
			              _CUPS_API_1_6;

/**** New in CUPS 1.7 ****/
extern ipp_attribute_t	*ippAddStringf(ipp_t *ipp, ipp_tag_t group,
			               ipp_tag_t value_tag, const char *name,
			               const char *language, const char *format,
			               ...) _CUPS_API_1_7;
extern ipp_attribute_t	*ippAddStringfv(ipp_t *ipp, ipp_tag_t group,
					ipp_tag_t value_tag, const char *name,
					const char *language,
					const char *format, va_list ap)
					_CUPS_API_1_7;
extern ipp_t		*ippNewResponse(ipp_t *request) _CUPS_API_1_7;


/*
 * C++ magic...
 */

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_CUPS_IPP_H_ */

/*
 * End of "$Id$".
 */
