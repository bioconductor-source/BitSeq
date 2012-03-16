#include<cstdlib>
extern "C"{
#include<stdint.h>
}


/*! @abstract the read is paired in sequencing, no matter whether it is mapped in a pair */
#define BAM_FPAIRED        1
/*! @abstract the read is mapped in a proper pair */
#define BAM_FPROPER_PAIR   2
/*! @abstract the read itself is unmapped; conflictive with BAM_FPROPER_PAIR */
#define BAM_FUNMAP         4
/*! @abstract the mate is unmapped */
#define BAM_FMUNMAP        8
/*! @abstract the read is mapped to the reverse strand */
#define BAM_FREVERSE      16
/*! @abstract the mate is mapped to the reverse strand */
#define BAM_FMREVERSE     32
/*! @abstract this is read1 */
#define BAM_FREAD1        64
/*! @abstract this is read2 */
#define BAM_FREAD2       128
/*! @abstract not primary alignment */
#define BAM_FSECONDARY   256
/*! @abstract QC failure */
#define BAM_FQCFAIL      512
/*! @abstract optical or PCR duplicate */
#define BAM_FDUP        1024
#define bam1_strand(b) (((b)->core.flag&BAM_FREVERSE) != 0)
#define bam1_mstrand(b) (((b)->core.flag&BAM_FMREVERSE) != 0)
#define bam1_cigar(b) ((uint32_t*)((b)->data + (b)->core.l_qname))
#define bam1_qname(b) ((char*)((b)->data))
#define bam1_seq(b) ((b)->data + (b)->core.n_cigar*4 + (b)->core.l_qname)
#define bam1_qual(b) ((b)->data + (b)->core.n_cigar*4 + (b)->core.l_qname + (((b)->core.l_qseq + 1)>>1))
#define bam1_seqi(s, i) ((s)[(i)/2] >> 4*(1-(i)%2) & 0xf)
#define bam1_aux(b) ((b)->data + (b)->core.n_cigar*4 + (b)->core.l_qname + (b)->core.l_qseq + ((b)->core.l_qseq + 1)/2)

/* moved to readDistribution.h
#define bam_init1() ((bam1_t*)calloc(1, sizeof(bam1_t)))
#define bam_destroy1(b) do { \
   if (b) { free((b)->data); free(b); }	\
} while (0)
*/


extern "C"{

typedef struct {
	int32_t n_targets;
	char **target_name;
	uint32_t *target_len;
	void *dict, *hash, *rg2lib;
	size_t l_text, n_text;
	char *text;
} bam_header_t;
typedef struct {
	int32_t tid;
	int32_t pos;
	uint32_t bin:16, qual:8, l_qname:8;
	uint32_t flag:16, n_cigar:16;
	int32_t l_qseq;
	int32_t mtid;
	int32_t mpos;
	int32_t isize;
} bam1_core_t;
typedef struct {
	bam1_core_t core;
	int l_aux, data_len, m_data;
	uint8_t *data;
} bam1_t;



typedef void *tamFile;
typedef void *bamFile;

	int sam_read1(tamFile fp, bam_header_t *header, bam1_t *b);
}


extern "C"{

typedef struct {
	int type;
	union {
		tamFile tamr;
		bamFile bam;
		FILE *tamw;
	} x;
	bam_header_t *header;
} samfile_t;


int samread(samfile_t *fp, bam1_t *b);
void samclose(samfile_t *fp);
samfile_t *samopen(const char *fn, const char *mode, const void *aux);

}
