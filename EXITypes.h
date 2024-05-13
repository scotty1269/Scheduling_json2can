/*
 * Copyright (C) 2007-2018 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 2017-03-02 
 * @contact Richard.Kuntschke@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



/**
 * \file 	EXITypes.h
 * \brief 	Basic type definitions and structs
 *
 */

#ifndef EXI_TYPES_H
#define EXI_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "EXIConfig.h"
#if EXI_STREAM == FILE_STREAM
#include <stdio.h>
#endif


/** Number of bits for each byte */
#define BITS_IN_BYTE 8

/** EXI Date-Time offset for year */
#define DATETIME_YEAR_OFFSET 2000
/** EXI Date-Time number of bits for monthDay */
#define DATETIME_NUMBER_BITS_MONTHDAY 9
/** EXI Date-Time number of bits for time */
#define DATETIME_NUMBER_BITS_TIME 17
/** EXI Date-Time number of bits for timezone */
#define DATETIME_NUMBER_BITS_TIMEZONE 11
/** EXI Date-Time month multiplicator */
#define DATETIME_MONTH_MULTIPLICATOR 32
/** EXI Date-Time offset for timzone minutes */
#define DATETIME_TIMEZONE_OFFSET_IN_MINUTES 896

/** Maximum integer value for uint */
#define UINT_MAX_VALUE 65535


/** EXI Float exponent special values */
#define FLOAT_EXPONENT_SPECIAL_VALUES -16384
/** EXI Float mantissa infinity */
#define FLOAT_MANTISSA_INFINITY 1
/** EXI Float minus mantissa infinity */
#define FLOAT_MANTISSA_MINUS_INFINITY -1
/** EXI Float not a number */
#define FLOAT_MANTISSA_NOT_A_NUMBER 0

/** \brief EXI Events */
typedef enum {
	/** Start Document SD */
	EXI_EVENT_START_DOCUMENT,
	/** End Document ED */
	EXI_EVENT_END_DOCUMENT,
	/** Start Element SE(qname) */
	EXI_EVENT_START_ELEMENT,
	/** Start Element SE(uri:*) */
	EXI_EVENT_START_ELEMENT_NS,
	/** Start Element SE(*) generic */
	EXI_EVENT_START_ELEMENT_GENERIC,
	/** Start Element SE(*) generic undeclared */
	EXI_EVENT_START_ELEMENT_GENERIC_UNDECLARED,
	/** End Element EE */
	EXI_EVENT_END_ELEMENT,
	/** End Element EE undeclared*/
	EXI_EVENT_END_ELEMENT_UNDECLARED,
	/** Characters CH */
	EXI_EVENT_CHARACTERS,
	/** Characters CH generic */
	EXI_EVENT_CHARACTERS_GENERIC,
	/** Characters CH generic undeclared */
	EXI_EVENT_CHARACTERS_GENERIC_UNDECLARED,
	/** Attribute AT(xsi:type) */
	EXI_EVENT_ATTRIBUTE_XSI_TYPE,
	/** Attribute AT(xsi:nil) */
	EXI_EVENT_ATTRIBUTE_XSI_NIL,
	/** Attribute AT(qname) */
	EXI_EVENT_ATTRIBUTE,
	/** Attribute AT(uri:*) */
	EXI_EVENT_ATTRIBUTE_NS,
	/** Attribute AT(*) generic */
	EXI_EVENT_ATTRIBUTE_GENERIC,
	/** Attribute AT(*) invalid value */
	EXI_EVENT_ATTRIBUTE_INVALID_VALUE,
	/** Attribute AT(*) any invalid value */
	EXI_EVENT_ATTRIBUTE_ANY_INVALID_VALUE,
	/** Attribute AT(*) generic undeclared */
	EXI_EVENT_ATTRIBUTE_GENERIC_UNDECLARED,
	/* error state */
	EXI_EVENT_ERROR
} exi_event_t;


/**
 * \brief 	Bit stream container
 *
 *	Structure for byteArray/file stream.
 *
 *	# General
 *	.size defines the maximum size of the byte array (see .data)
 *
 *	.data points to the input/output array of bytes (unsigned char*).
 *
 *	.pos has to be set to an pointer to an 32 bit long unsigned integer (uint32_t *)
 *	 as this variable is read/write.
 *	 Therefore it is best practice to declare the variable itself and use the &-operator
 *	 to assign the address. The value of that variable points to the position inside the
 *	 buffer where the stream begins. Which is usually the first (0th) byte but can also be
 *	 another value if there more information transferred in that stream.
 *	 After processing .pos points to the next "available" byte (if any left).
 *
 *	.buffer has to be set to 0 for internal use only (single byte buffer)
 *
 *	# Receiving data (input)
 *	.capacity is used for addressing single bits in the actual byte (see .buffer)
 *	 and has to be set to 0, which means there are 0 bits read so far and a new
 *	 byte needs to be read from the input stream/data-array to the current byte buffer.
 *
 *	# Sending data (output)
 *	.capacity is used for addressing single bits in the actual byte (see .buffer)
 *	 and has to be set to 8, which means there are still 8 bits left to fill up
 *	 the current byte buffer before writing the final byte to the output stream/data-array.
 *
 */
typedef struct {
#if EXI_STREAM == BYTE_ARRAY
	/**	byte array size */
	size_t size;
	/**	byte array data */
	uint8_t* data;
	/**	byte array next position in array */
	size_t* pos;
#endif
#if EXI_STREAM == FILE_STREAM
	/** file pointer */
	FILE *file;
#endif
	/** Current byte buffer*/
	uint8_t buffer;
	/** Remaining bit capacity in current byte buffer*/
	uint8_t capacity;
} bitstream_t;


/** \brief EXI Value Datatypes */
typedef enum {
	/** Binary Base64 */
	EXI_DATATYPE_BINARY_BASE64,
	/** Binary Hex */
	EXI_DATATYPE_BINARY_HEX,
	/** Boolean */
	EXI_DATATYPE_BOOLEAN,
	/** Boolean with Facets */
	EXI_DATATYPE_BOOLEAN_FACET,
	/** Decimal */
	EXI_DATATYPE_DECIMAL,
	/** Float & Double */
	EXI_DATATYPE_FLOAT,
	/** N-Bit Unsigned Integer */
	EXI_DATATYPE_NBIT_UNSIGNED_INTEGER,
	/** Unsigned Integer */
	EXI_DATATYPE_UNSIGNED_INTEGER,
	/** (Signed) Integer */
	EXI_DATATYPE_INTEGER,
	/** Datetime */
	EXI_DATATYPE_DATETIME,
	/** String */
	EXI_DATATYPE_STRING,
	/** Restricted Character Set String */
	EXI_DATATYPE_RCS_STRING,
	/** Enumeration */
	EXI_DATATYPE_ENUMERATION,
	/** List */
	EXI_DATATYPE_LIST,
	/** QName (e.g. xsi:type) */
	EXI_DATATYPE_QNAME
} exi_datatype_t;


/** \brief EXI Integer Value types */
typedef enum {
	/** Unsigned Integer 8 bits */
	EXI_UNSIGNED_INTEGER_8,
	/** Unsigned Integer 16 bits */
	EXI_UNSIGNED_INTEGER_16,
	/** Unsigned Integer 32 bits */
	EXI_UNSIGNED_INTEGER_32,
	/** Unsigned Integer 64 bits */
	EXI_UNSIGNED_INTEGER_64,
	/** (Signed) Integer 8 bits */
	EXI_INTEGER_8,
	/** (Signed) Integer 16 bits */
	EXI_INTEGER_16,
	/** (Signed) Integer 32 bits */
	EXI_INTEGER_32,
	/** (Signed) Integer 64 bits */
	EXI_INTEGER_64
} exi_integer_type_t;


/** \brief EXI Datetime types */
typedef enum {
	/** gYear */
	EXI_DATETIME_GYEAR,
	/** gYearMonth */
	EXI_DATETIME_GYEARMONTH,
	/** date */
	EXI_DATETIME_DATE,
	/** datetime */
	EXI_DATETIME_DATETIME,
	/** gMonth */
	EXI_DATETIME_GMONTH,
	/** gMonthDay */
	EXI_DATETIME_GMONTHDAY,
	/** gDay */
	EXI_DATETIME_GDAY,
	/** time */
	EXI_DATETIME_TIME
} exi_datetime_type_t;


/** \brief String value type */
typedef enum {
	/** value miss */
	EXI_STRING_VALUE_MISS,
	/** value local-hit */
	EXI_STRING_VALUE_LOCAL_HIT,
	/** value global-hit */
	EXI_STRING_VALUE_GLOBAL_HIT
} exi_string_value_type_t;

/** \brief EXI string character */
/* Note: define whether you wan't to support ASCII only or UCS */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
typedef char exi_string_character_t;
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
typedef uint32_t exi_string_character_t;
#endif /* STRING_REPRESENTATION_UCS */



/** \brief Universal Character Set (UCS) strings */
typedef struct {
	/** container size  */
	size_t size;
	/** string character container */
	exi_string_character_t* characters;
	/** current string length == number of code-points, (len <= size) */
	size_t len;
} exi_string_t;


/** \brief String value */
typedef struct {
	/** value type (e.g., miss, local-hit, global-hit) */
	exi_string_value_type_t type;
	/** miss entry */
	exi_string_t miss;
	/** (local) hit entry */
	size_t localID;
	/** (global) hit entry */
	size_t globalID;
} exi_string_value_t;


/** \brief Restricted Characeter Set */
typedef struct {
	/** size */
	size_t size;
	/** rcs codepoints */
	exi_string_character_t* characters;
	/** character coding length (less than 256 characters) */
	uint8_t codingLength;
} exi_rcs_t;


/** \brief Byte value container */
typedef struct {
	/** bytes array size */
	size_t size;
	/** bytes array data container */
	uint8_t* data;
	/** bytes array length (len <= size) */
	size_t len;
} exi_bytes_t;


/** \brief Integer value container */
typedef struct {
	/** type */
	exi_integer_type_t type;
	union {
		/* (signed) values */
		/** (signed) int 8 bits */
		int8_t int8;
		/** (signed) int 16 bits */
		int16_t int16;
		/** (signed) int 32 bits */
		int32_t int32;
		/** (signed) int 64 bits */
		int64_t int64;
		/* unsigned values */
		/** unsigned int 8 bits */
		uint8_t uint8;
		/** unsigned int 16 bits */
		uint16_t uint16;
		/** unsigned int 32 bits */
		uint32_t uint32;
		/** unsigned int 64 bits */
		uint64_t uint64;
	} val;
} exi_integer_t;


/** \brief Float value container */
typedef struct {
	/** range of the mantissa is -(2^63) to 2^63-1 */
	int64_t mantissa;
	/** range of the exponent is - (2^14-1) to 2^14-1 */
	int16_t exponent; /* base-10 */
} exi_float_me_t;


/** \brief Decimal value container */
typedef struct {
	/** a sign value */
	int negative;
	/** represents the integral portion of the Decimal */
	exi_integer_t integral;
	/** represents the fractional portion of the Decimal with the digits in reverse order to preserve leading zeros */
	exi_integer_t reverseFraction;
} exi_decimal_t;


/** \brief Datetime value container */
typedef struct {
	/** datetime type */
	exi_datetime_type_t type;
	/** Datetime value for year */
	int32_t year;
	/** Datetime value for monthDay */
	uint32_t monthDay;
	/** Datetime value for time */
	uint32_t time;
	/** Datetime value for presenceFractionalSecs */
	int presenceFractionalSecs;
	/** Datetime value for fractionalSecs */
	uint32_t fractionalSecs;
	/** Datetime value for presenceTimezone */
	int presenceTimezone;
	/** Datetime value for timezone */
	uint32_t timezone;
} exi_datetime_t;


/** \brief List value container */
typedef struct {
	/** list item type */
	exi_datatype_t type;
	/** number of items */
	size_t len;
	/* Special datatype: integer */
	/* exi_integer_type_t intType;*/
	/** Special datatype: datetime */
	exi_datetime_type_t datetimeType;
} exi_list_t;


/** \brief Efficient qname */
typedef struct {
	/** namespace URI ID*/
	size_t namespaceURI;
	/** local name ID*/
	size_t localPart;
} exi_eqname_t;


/** \brief Name entry type */
typedef enum {
	/** As known IDs */
	EXI_NAME_ENTRY_TYPE_ID,
	/** As String */
	EXI_NAME_ENTRY_TYPE_STRING_AND_ID
} exi_name_entry_type_t;


/** \brief Name entry */
typedef struct {
	/** type */
	exi_name_entry_type_t type;
	/** entry ID */
	size_t id;
	/** entry string */
	exi_string_t str;
} exi_name_entry_t;


/** \brief Qualified name */
typedef struct {
	/** Uri */
	exi_name_entry_t uri;
	/** LocalName */
	exi_name_entry_t localName;
} exi_qname_t;


/*TODO Doxygen Documentation */






/* ==================================== */
/* URI and LocalName Entries */
typedef struct exiNameTablePrepopulated {
	/* number of namespaces AND length name-partitions array */
	size_t len;
	/* number of localName entries divided by URI */
	size_t* localNames;
} exi_name_table_prepopulated_t;

#define EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_ENTRIES 25

typedef enum {
	EXI_NAME_PARTITION_URI, EXI_NAME_PARTITION_LOCALNAME
} exi_name_partition_type_t;

typedef struct {
	char* uri;
	size_t uriID;
} exi_uri_partition_t;

typedef struct {
	char* localName;
	size_t localNameID;
	size_t uriID;
} exi_localname_partition_t;

typedef struct {
	exi_name_partition_type_t namePartitionType;
	struct {
		exi_uri_partition_t uriPartition;
		exi_localname_partition_t localNamePartition;
	} entry;
} exi_name_partition_t;

typedef struct exiNameTableRuntime {
	/* maximum number of characters in the name partitions entries PLUS null terminators */
	/* char characters[EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_CHARACTERS + EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_ENTRIES]; */
	/* uint16_t numberOfUsedCharacters; *//* initially zero <= EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_CHARACTERS */
	/* maximum number of name partitions entries. Name partitions entries consist in all uri, and local-name partition entries */
	exi_name_partition_t
			namePartitionsEntries[EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_ENTRIES];
	/* uint16_t numberOfUsedNamePartitions; *//* initially zero */
	/* added entries */
	size_t addedUriEntries; /* initially zero */
	size_t addedLocalNameEntries; /* initially zero */
} exi_name_table_runtime_t;


/* StartTagContent grammar initially empty */
/* ElementContent grammar has EE per default */
typedef struct {
	size_t namespaceUriID;
	size_t localNameID;
	size_t numberOfProductions;
	int hasXsiType; /* StartTagContent only */
	int hasEE; /* ElementContentper default TRUE */
} exi_runtime_element_t;

/* Note: We do have twice as many runtime grammars (StartTagContent and ElementContent)*/
#define MAX_NUMBER_OF_RUNTIME_ELEMENTS 80



/* ==================================== */
/* Value string table */
typedef struct exiValueStringTableEntry {
	/** Qualified namespace URI */
	size_t namespaceUriID;
	/** Qualified localName */
	size_t localNameID;
	/** Local Value ID */
	size_t localValueID;
	/** String */
	exi_string_t str;
} exi_value_string_table_entry_t;

typedef struct exiValueStringTable {
	/** maximum number of global string table entry size */
	size_t size;
	/** string table entry array container */
	exi_value_string_table_entry_t* strs;
	/** current number of string table entries (len <= size) */
	size_t len;
} exi_value_string_table_t;

/* typedef struct { */
	/** number of global strings */
	/* uint16_t numberOfGlobalStrings; */
	/** size of local-names container */
	/* uint16_t sizeLocalStrings; */
	/** number of local strings container */
	/* uint16_t* numberOfLocalStrings; */
	/** string values */
/*	exi_value_string_table_t* valueStringTable;
} exi_value_table_t;*/

typedef struct {
	/** stack of grammar states */
	int16_t grammarStack[EXI_ELEMENT_STACK_SIZE];
	/** stack of grammar elements / qnameIDs */
	exi_eqname_t elementStack[EXI_ELEMENT_STACK_SIZE];
	/** stack index for both stacks */
	size_t stackIndex;

	/** event-code */
	uint32_t eventCode;

	/** name table entries, pre-populated */
	exi_name_table_prepopulated_t* nameTablePrepopulated;
	/** name table entries, at runtime */
	exi_name_table_runtime_t* nameTableRuntime;

	/** next qname ID */
	size_t nextQNameID;

	/** string table entries */
	exi_value_string_table_t* stringTable;

	/** runtime built-in element grammars - numbers */
	size_t numberOfRuntimeGrammars;
	/** runtime built-in element grammars */
	exi_runtime_element_t runtimeGrammars[MAX_NUMBER_OF_RUNTIME_ELEMENTS * 2];
} exi_state_t;

typedef struct {
	/* type of value */
	exi_datatype_t type;

	/* base types */
	int boolean;
	uint32_t enumeration;

	/* complex types: Integers, Bytes, Strings and Lists are not native types anymore */
	exi_integer_t integer;
	exi_bytes_t binary;
	exi_string_value_t str;
	exi_float_me_t float_me;
	exi_decimal_t decimal;
	exi_datetime_t datetime;
	exi_list_t list;
	exi_eqname_t eqname;
} exi_value_t;


#ifdef __cplusplus
}
#endif

#endif
