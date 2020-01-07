#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define H264_MAX_SPS_PPS_SIZE 200
#define AST_FORMAT_ATTR_SIZE 16

// #if !defined(ast_strdupa) && defined(__GNUC__)
/*!
 * \brief duplicate a string in memory from the stack
 * \param s The string to duplicate
 *
 * This macro will duplicate the given string.  It returns a pointer to the stack
 * allocatted memory for the new string.
 */
// #define ast_strdupa(s)                                                    \
// 	(__extension__                                                    \
// 	({                                                                \
// 		const char *__old = (s);                                  \
// 		size_t __len = strlen(__old) + 1;                         \
// 		char *__new = __builtin_alloca(__len);                    \
// 		memcpy (__new, __old, __len);                             \
// 		__new;                                                    \
// 	}))
// #endif

/*! \brief This structure contains the buffer used for format attributes */
struct ast_format_attr {
	/*! The buffer formats can use to represent attributes */
	uint32_t format_attr[AST_FORMAT_ATTR_SIZE];
	/*! If a format's payload needs to pass through that a new marker is required
	 * for RTP, this variable will be set. */
	uint8_t rtp_marker_bit;
};

//faked vulnerable function
static int h264_format_attr_sdp_parse(struct ast_format_attr *format_attr, char *attributes)
{
    //TODO: analyse exploit relevance
	//char *attribs = ast_strdupa(attributes); //copy content of attributes into new mem area and let attribs point to it..
	//ich brauche nicht kopieren, mir ist die aenderung von strsep egal...
	char *attribs = attributes; 
	char *attrib;


    // brauch ich nicht, setzt nur die werte
	//format_attr->format_attr[H264_ATTR_KEY_REDUNDANT_PIC_CAP] = H264_ATTR_KEY_UNSET;
	//format_attr->format_attr[H264_ATTR_KEY_PARAMETER_ADD] = H264_ATTR_KEY_UNSET;
	//format_attr->format_attr[H264_ATTR_KEY_PACKETIZATION_MODE] = H264_ATTR_KEY_UNSET;
	//format_attr->format_attr[H264_ATTR_KEY_LEVEL_ASYMMETRY_ALLOWED] = H264_ATTR_KEY_UNSET;

	printf("attribs: %s", attribs);

	while ((attrib = strsep(&attribs, ";"))) {
		unsigned int val;
		unsigned long int val2;
		char sps[H264_MAX_SPS_PPS_SIZE], pps[H264_MAX_SPS_PPS_SIZE];

		printf("attrib: %s", attrib);

		//auch irrelevant
		//if (sscanf(attrib, "profile-level-id=%lx", &val2) == 1) {
			//format_attr->format_attr[H264_ATTR_KEY_PROFILE_IDC] = ((val2 >> 16) & 0xFF);
			//format_attr->format_attr[H264_ATTR_KEY_PROFILE_IOP] = ((val2 >> 8) & 0xFF);
			//format_attr->format_attr[H264_ATTR_KEY_LEVEL] = (val2 & 0xFF);
		//} else 
		printf("DEBUG pps: %p\n", pps);
		printf("DEBUG sps: %p\n", sps);
		if (sscanf(attrib, "sprop-parameter-sets=%[^','],%s", sps, pps) == 2) {
			printf("sps %d %s\n", strlen(sps), sps);
			printf("pps %d %s\n", strlen(pps), pps);
			//unsigned char spsdecoded[H264_MAX_SPS_PPS_SIZE] = { 0, }, ppsdecoded[H264_MAX_SPS_PPS_SIZE] = { 0, };
			//int i;

			//ast_base64decode(spsdecoded, sps, sizeof(spsdecoded));
			//ast_base64decode(ppsdecoded, pps, sizeof(ppsdecoded));

			//format_attr->format_attr[H264_ATTR_KEY_SPS_LEN] = 0;
			//format_attr->format_attr[H264_ATTR_KEY_PPS_LEN] = 0;

			//for (i = 0; i < H264_MAX_SPS_PPS_SIZE; i++) {
			//	if (spsdecoded[i]) {
					//format_attr->format_attr[H264_ATTR_KEY_SPS + i] = spsdecoded[i];
					//format_attr->format_attr[H264_ATTR_KEY_SPS_LEN]++;
			//	}
			//	if (ppsdecoded[i]) {
					//format_attr->format_attr[H264_ATTR_KEY_PPS + i] = ppsdecoded[i];
					//format_attr->format_attr[H264_ATTR_KEY_PPS_LEN]++;
			//	}
			//}
		} 
        
        //length within sscanf is checked...
        // else if (sscanf(attrib, "max-mbps=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_MBPS] = val;
		// } else if (sscanf(attrib, "max-fs=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_FS] = val;
		// } else if (sscanf(attrib, "max-cpb=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_CPB] = val;
		// } else if (sscanf(attrib, "max-dpb=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_DPB] = val;
		// } else if (sscanf(attrib, "max-br=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_BR] = val;
		// } else if (sscanf(attrib, "max-smbps=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_SMBPS] = val;
		// } else if (sscanf(attrib, "max-fps=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_FPS] = val;
		// } else if (sscanf(attrib, "redundant-pic-cap=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_REDUNDANT_PIC_CAP] = val;
		// } else if (sscanf(attrib, "parameter-add=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_PARAMETER_ADD] = val;
		// } else if (sscanf(attrib, "packetization-mode=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_PACKETIZATION_MODE] = val;
		// } else if (sscanf(attrib, "sprop-interleaving-depth=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_SPROP_INTERLEAVING_DEPTH] = val;
		// } else if (sscanf(attrib, "sprop-deint-buf-req=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_SPROP_DEINT_BUF_REQ] = val;
		// } else if (sscanf(attrib, "deint-buf-cap=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_DEINT_BUF_CAP] = val;
		// } else if (sscanf(attrib, "sprop-init-buf-time=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_SPROP_INIT_BUF_TIME] = val;
		// } else if (sscanf(attrib, "sprop-max-don-diff=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_SPROP_MAX_DON_DIFF] = val;
		// } else if (sscanf(attrib, "max-rcmd-nalu-size=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_MAX_RCMD_NALU_SIZE] = val;
		// } else if (sscanf(attrib, "level-asymmetry-allowed=%30u", &val) == 1) {
		// 	format_attr->format_attr[H264_ATTR_KEY_LEVEL_ASYMMETRY_ALLOWED] = val;
		// }
	}

	return 0;
}


#define BUFFER_SIZE 512

//send malicious input to vulnerable function
int main(int argc, char *argv[]) {

    printf("Hallo Welt!\n");

	struct ast_format_attr attr;

	char *f;
	char buffer[BUFFER_SIZE];

	//simulate reading sip attributes from network partner...
	f = fgets(buffer, BUFFER_SIZE - 1, stdin);


	h264_format_attr_sdp_parse(&attr, buffer);


    return 0;
}