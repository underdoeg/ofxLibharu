
class ofxLibharuError
{
public:
	ofxLibharuError() {
		parseErrorString();
	};
	
	~ofxLibharuError() {};
	
	string getErrorInfo(int id){
		return errorInfos[id];
	}

private:
	void parseErrorString() {
		vector<string> lines = ofSplitString(errorString,";");
		for(int i=0; i<lines.size(); i++){
			vector<string> items = ofSplitString(lines[i],", ");
			
			int num = (int)strtol(items[1].c_str(), NULL, 16);
			errorInfos[num] = items[2];
		}
	}
	
	map<int, string> errorInfos;
	
	string errorString = "HPDF_ARRAY_COUNT_ERR, 0x1001, Internal error. Data consistency was lost.;\
HPDF_ARRAY_ITEM_NOT_FOUND, 0x1002, Internal error. Data consistency was lost.;\
HPDF_ARRAY_ITEM_UNEXPECTED_TYPE, 0x1003, Internal error. Data consistency was lost.;\
HPDF_BINARY_LENGTH_ERR, 0x1004, Data length > HPDF_LIMIT_MAX_STRING_LEN.;\
HPDF_CANNOT_GET_PALLET, 0x1005, Cannot get pallet data from PNG image.;\
HPDF_DICT_COUNT_ERR, 0x1007, Dictionary elements > HPDF_LIMIT_MAX_DICT_ELEMENT;\
HPDF_DICT_ITEM_NOT_FOUND, 0x1008, Internal error. Data consistency was lost.;\
HPDF_DICT_ITEM_UNEXPECTED_TYPE, 0x1009, Internal error. Data consistency was lost.;\
HPDF_DICT_STREAM_LENGTH_NOT_FOUND, 0x100A, Internal error. Data consistency was lost.;\
HPDF_DOC_ENCRYPTDICT_NOT_FOUND, 0x100B, HPDF_SetEncryptMode() or HPDF_SetPermission() called before password set.;\
HPDF_DOC_INVALID_OBJECT, 0x100C, Internal error. Data consistency was lost.;\
HPDF_DUPLICATE_REGISTRATION, 0x100E, Tried to re-register a registered font.;\
HPDF_EXCEED_JWW_CODE_NUM_LIMIT, 0x100F, Cannot register a character to the Japanese word wrap characters list.;\
HPDF_ENCRYPT_INVALID_PASSWORD, 0x1011, 1. Tried to set the owner password to NULL. 2. Owner and user password are the same.;\
HPDF_ERR_UNKNOWN_CLASS, 0x1013, Internal error. Data consistency was lost.;\
HPDF_EXCEED_GSTATE_LIMIT, 0x1014, Stack depth > HPDF_LIMIT_MAX_GSTATE.;\
HPDF_FAILD_TO_ALLOC_MEM, 0x1015, Memory allocation failed.;\
HPDF_FILE_IO_ERROR, 0x1016, File processing failed. (Detailed code is set.);\
HPDF_FILE_OPEN_ERROR, 0x1017, Cannot open a file. (Detailed code is set.);\
HPDF_FONT_EXISTS, 0x1019, Tried to load a font that has been registered.;\
HPDF_FONT_INVALID_WIDTHS_TABLE, 0x101A, 1. Font-file format is invalid. 2. Internal error. Data consistency was lost.;\
HPDF_INVALID_AFM_HEADER, 0x101B, Cannot recognize header of afm file.;\
HPDF_INVALID_ANNOTATION, 0x101C, Specified annotation handle is invalid.;\
HPDF_INVALID_BIT_PER_COMPONENT, 0x101E, Bit-per-component of a image which was set as mask-image is invalid.;\
HPDF_INVALID_CHAR_MATRICS_DATA, 0x101F, Cannot recognize char-matrics-data of afm file.;\
HPDF_INVALID_COLOR_SPACE, 0x1020, 1. Invalid color_space parameter of HPDF_LoadRawImage. 2. Color-space of a image which was set as mask-image is invalid. 3. Invoked function invalid in present color-space.;\
HPDF_INVALID_COMPRESSION_MODE, 0x1021, Invalid value set when invoking HPDF_SetCommpressionMode().;\
HPDF_INVALID_DATE_TIME, 0x1022, An invalid date-time value was set.;\
HPDF_INVALID_DESTINATION, 0x1023, An invalid destination handle was set.;\
HPDF_INVALID_DOCUMENT, 0x1025, An invalid document handle was set.;\
HPDF_INVALID_DOCUMENT_STATE, 0x1026, Function invalid in the present state was invoked.;\
HPDF_INVALID_ENCODER, 0x1027, An invalid encoder handle was set.;\
HPDF_INVALID_ENCODER_TYPE, 0x1028, Combination between font and encoder is wrong.;\
HPDF_INVALID_ENCODING_NAME, 0x102B, An Invalid encoding name is specified.;\
HPDF_INVALID_ENCRYPT_KEY_LEN, 0x102C, Encryption key length is invalid.;\
HPDF_INVALID_FONTDEF_DATA, 0x102D, 1. An invalid font handle was set. 2. Unsupported font format.;\
HPDF_INVALID_FONTDEF_TYPE, 0x102E, Internal error. Data consistency was lost.;\
HPDF_INVALID_FONT_NAME, 0x102F, Font with the specified name is not found.;\
HPDF_INVALID_IMAGE, 0x1030, Unsupported image format.;\
HPDF_INVALID_JPEG_DATA, 0x1031, Unsupported image format.;\
HPDF_INVALID_N_DATA, 0x1032, Cannot read a postscript-name from an afm file.;\
HPDF_INVALID_OBJECT, 0x1033, 1. An invalid object is set. 2. Internal error. Data consistency was lost.;\
HPDF_INVALID_OBJ_ID, 0x1034, Internal error. Data consistency was lost.;\
HPDF_INVALID_OPERATION, 0x1035, Invoked HPDF_Image_SetColorMask() against the image-object which was set a mask-image.;\
HPDF_INVALID_OUTLINE, 0x1036, An invalid outline-handle was specified.;\
HPDF_INVALID_PAGE, 0x1037, An invalid page-handle was specified.;\
HPDF_INVALID_PAGES, 0x1038, An invalid pages-handle was specified. (internal error);\
HPDF_INVALID_PARAMETER, 0x1039, An invalid value is set.;\
HPDF_INVALID_PNG_IMAGE, 0x103B, Invalid PNG image format.;\
HPDF_INVALID_STREAM, 0x103C, Internal error. Data consistency was lost.;\
HPDF_MISSING_FILE_NAME_ENTRY, 0x103D, Internal error. _FILE_NAME entry for delayed loading is missing.;\
HPDF_INVALID_TTC_FILE, 0x103F, Invalid .TTC file format.;\
HPDF_INVALID_TTC_INDEX, 0x1040, Index parameter > number of included fonts.;\
HPDF_INVALID_WX_DATA, 0x1041, Cannot read a width-data from an afm file.;\
HPDF_ITEM_NOT_FOUND, 0x1042, Internal error. Data consistency was lost.;\
HPDF_LIBPNG_ERROR, 0x1043, Error returned from PNGLIB while loading image.;\
HPDF_NAME_INVALID_VALUE, 0x1044, Internal error. Data consistency was lost.;\
HPDF_NAME_OUT_OF_RANGE, 0x1045, Internal error. Data consistency was lost.;\
HPDF_PAGES_MISSING_KIDS_ENTRY, 0x1049, Internal error. Data consistency was lost.;\
HPDF_PAGE_CANNOT_FIND_OBJECT, 0x104A, Internal error. Data consistency was lost.;\
HPDF_PAGE_CANNOT_GET_ROOT_PAGES, 0x104B, Internal error. Data consistency was lost.;\
HPDF_PAGE_CANNOT_RESTORE_GSTATE, 0x104C, There are no graphics-states to be restored.;\
HPDF_PAGE_CANNOT_SET_PARENT, 0x104D, Internal error. Data consistency was lost.;\
HPDF_PAGE_FONT_NOT_FOUND, 0x104E, The current font is not set.;\
HPDF_PAGE_INVALID_FONT, 0x104F, An invalid font-handle was specified.;\
HPDF_PAGE_INVALID_FONT_SIZE, 0x1050, An invalid font-size was set.;\
HPDF_PAGE_INVALID_GMODE, 0x1051, See Graphics mode.;\
HPDF_PAGE_INVALID_INDEX, 0x1052, Internal error. Data consistency was lost.;\
HPDF_PAGE_INVALID_ROTATE_VALUE, 0x1053, Specified value is not multiple of 90.;\
HPDF_PAGE_INVALID_SIZE, 0x1054, An invalid page-size was set.;\
HPDF_PAGE_INVALID_XOBJECT, 0x1055, An invalid image-handle was set.;\
HPDF_PAGE_OUT_OF_RANGE, 0x1056, The specified value is out of range.;\
HPDF_REAL_OUT_OF_RANGE, 0x1057, The specified value is out of range.;\
HPDF_STREAM_EOF, 0x1058, Unexpected EOF marker was detected.;\
HPDF_STREAM_READLN_CONTINUE, 0x1059, Internal error. Data consistency was lost.;\
HPDF_STRING_OUT_OF_RANGE, 0x105B, The length of the text is too long.;\
HPDF_THIS_FUNC_WAS_SKIPPED, 0x105C, Function not executed because of other errors.;\
HPDF_TTF_CANNOT_EMBEDDING_FONT, 0x105D, Font cannot be embedded. (license restriction);\
HPDF_TTF_INVALID_CMAP, 0x105E, Unsupported ttf format. (cannot find unicode cmap);\
HPDF_TTF_INVALID_FOMAT, 0x105F, Unsupported ttf format.;\
HPDF_TTF_MISSING_TABLE, 0x1060, Unsupported ttf format. (cannot find a necessary table);\
HPDF_UNSUPPORTED_FONT_TYPE, 0x1061, Internal error. Data consistency was lost.;\
HPDF_UNSUPPORTED_FUNC, 0x1062, 1. Library not configured to use PNGLIB. 2. Internal error. Data consistency was lost.;\
HPDF_UNSUPPORTED_JPEG_FORMAT, 0x1063, Unsupported JPEG format.;\
HPDF_UNSUPPORTED_TYPE1_FONT, 0x1064, Failed to parse .PFB file.;\
HPDF_XREF_COUNT_ERR, 0x1065, Internal error. Data consistency was lost.;\
HPDF_ZLIB_ERROR, 0x1066, Error while executing ZLIB function.;\
HPDF_INVALID_PAGE_INDEX, 0x1067, An invalid page index was passed.;\
HPDF_INVALID_URI, 0x1068, An invalid URI was set.;\
HPDF_PAGELAYOUT_OUT_OF_RANGE, 0x1069, An invalid page-layout was set.;\
HPDF_PAGEMODE_OUT_OF_RANGE, 0x1070, An invalid page-mode was set.;\
HPDF_PAGENUM_STYLE_OUT_OF_RANGE, 0x1071, An invalid page-num-style was set.;\
HPDF_ANNOT_INVALID_ICON, 0x1072, An invalid icon was set.;\
HPDF_ANNOT_INVALID_BORDER_STYLE, 0x1073, An invalid border-style was set.;\
HPDF_PAGE_INVALID_DIRECTION, 0x1074, An invalid page-direction was set.;\
HPDF_INVALID_FONT, 0x1075, An invalid font-handle was specified.";
};
