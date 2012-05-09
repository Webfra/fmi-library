/*
    Copyright (C) 2012 Modelon AB

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/** \file fmi_import_context.h
*  \brief Import context is the entry point to the library. It is used to initialize, unzip, get FMI version and start parsing.
*/

#ifndef FMI_IMPORT_CONTEXT_H_
#define FMI_IMPORT_CONTEXT_H_

#include <stddef.h>
#include <config_fmilib.h>
#include <Common/jm_callbacks.h>
#include <Common/fmi_xml_context.h>

#ifdef __cplusplus
extern "C" {
#endif

	
/** \addtogroup fmi_import FMI import library
@{
*/

/** \brief FMI version independent library context. 
	Opaque struct returned from fmi_import_allocate_context()
*/
typedef fmi_xml_context_t fmi_import_context_t ;

/** \brief Create fmi_import_context_t structure.
	@param callbacks - a pointer to the library callbacks for memory management and logging. May be NULL if defaults are utilized.
	@return A new structure if memory allocation was successful.
*/
static fmi_import_context_t* fmi_import_allocate_context( jm_callbacks* callbacks) {
	FMILIB_TRACE("Inside fmi_import_allocate_context\n");
	return fmi_xml_allocate_context(callbacks);
}

/**
	\brief Free memory allocated for the library context.
	@param c - library context allocated by fmi_import_allocate_context()
*/
static void fmi_import_free_context( fmi_import_context_t* c) {
	fmi_xml_free_context(c);
}

/**
	\brief Unzip an FMU specified by the fileName into directory dirName and parse XML to get FMI standard version.
	@param c - library context.
	@param fileName - an FMU file name.
	@param dirName - a directory name where the FMU should be unpacked
*/
fmi_version_enu_t fmi_import_get_fmi_version( fmi_import_context_t* c, const char* fileName, const char* dirName);

/**
	\brief FMU version 1.0 object
*/
typedef struct fmi1_import_t fmi1_import_t;

/**
	\brief Parse XML file found in the directory dirName.
	\param c - library context.
	\param dirName - a directory where the FMU was unpacked and XML file is present.
*/
fmi1_import_t* fmi1_import_parse_xml( fmi_import_context_t* c, const char* dirName);

/** \addtogroup  fmi1_import
@}
*/

#ifdef __cplusplus
}
#endif
#endif
