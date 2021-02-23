/* mmsdec.c
 * Test code for mms decoder
 *
 * $Id: $
 *
 * Xplico - Internet Traffic Decoder
 * By Gianluca Costa <g.costa@xplico.org>
 * Copyright 2007-2013 Gianluca Costa & Andrea de Franceschi. Web: www.xplico.org
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include <stdio.h>
#include <string.h>

#include "mms_decode.h"

#define MMS_RAW_DIM  1024*5000


void Usage(char *argv[])
{ 
    printf("Version: %s\n", MMSDEC_VER);
    printf("Usage:\n");
    printf("\t%s <mms_file>\n\n", argv[0]);
}

int Report(mms_message *msg)
{
    int i;
    FILE *fp;

    fp = fopen("./report.txt", "w");

    fprintf(fp, "Versrion %s\n", msg->version);
    printf("Versrion %s\n", msg->version);
    if (msg->msg_type != NULL) {
        fprintf(fp, "Message type: %s\n", msg->msg_type);
        printf("Message type: %s\n", msg->msg_type);
    }
    if (msg->cont_type != NULL) {
        fprintf(fp, "Content type: %s\n", msg->cont_type);
        printf("Content type: %s\n", msg->cont_type);
    }
    if (msg->from != NULL) {
        fprintf(fp, "From: %s\n", msg->from);
        printf("From: %s\n", msg->from);
    }
    if (msg->to != NULL) {
        fprintf(fp, "To: %s\n", msg->to);
        printf("To: %s\n", msg->to);
    }
    if (msg->cc != NULL) {
        fprintf(fp, "CC: %s\n", msg->cc);
        printf("CC: %s\n", msg->cc);
    }
    if (msg->bcc != NULL) {
        fprintf(fp, "Bcc: %s\n", msg->bcc);
        printf("Bcc: %s\n", msg->bcc);
    }
    if (msg->subject != NULL) {
        fprintf(fp, "Subject: %s\n", msg->subject);
        printf("Subject: %s\n", msg->subject);
    }

    if (msg->part != NULL) {
        for (i=0; i!=msg->nparts; i++) {
            fprintf(fp, "Part %i\n", i+1);
            printf("Part %i\n", i+1);
            if (msg->part[i].ctype != NULL) {
                fprintf(fp, "  ctype: %s\n", msg->part[i].ctype);
                printf("  ctype: %s\n", msg->part[i].ctype);
            }
            if (msg->part[i].name != NULL && msg->part[i].path != NULL) {
                fprintf(fp, "  name: %s\n", msg->part[i].name);
                printf("  name: %s\n", msg->part[i].name);
                fprintf(fp, "  size: %i\n", msg->part[i].size);
                printf("  size: %i\n", msg->part[i].size);
                rename(msg->part[i].path, msg->part[i].name);
            }
            else {
                if (msg->part[i].name != NULL) {
                    fprintf(fp, "  name: %s\n", msg->part[i].name);
                    printf("  name: %s\n", msg->part[i].name);
                }
                if (msg->part[i].path != NULL) {
                    fprintf(fp, "  path: %s\n", msg->part[i].path);
                    printf("  path: %s\n", msg->part[i].path);
                    fprintf(fp, "  size: %i\n", msg->part[i].size);
                    printf("  size: %i\n", msg->part[i].size);
                }
            }
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{
    int len;
    char *file = argv[1];
    unsigned char mms_raw[MMS_RAW_DIM];
    mms_message msg;
    FILE *fp;

    if (argc != 2) {
        Usage(argv);
        return 0;
    }

    fp = fopen(file, "r");

    printf("mmdec version %s\n", MMSDEC_VER);
    if (fp != NULL) {
        printf("MMS contents and report:\n");
        printf("\n---- START ----\n");
        len = fread(mms_raw, 1, MMS_RAW_DIM, fp);
        memset(&msg, 0, sizeof(mms_message));
        MMSDecode(&msg, mms_raw, len, ".");
        Report(&msg);
        MMSFree(&msg);
        fclose(fp);
        printf("---- END ----\n\n");
    }

    return 0;
}
