/*
 *  emails.c
 *
 *  Given a list of email addresses in "full name <email address>" format,
 *  print only the email addresses, with each of the email addresses on
 *  its own line.
 *
 *  --------------------------------------------------------------------------------------------
 *
 *  Copyright 2023 Avery Spencer
 * 
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *    Redistributions of source code must retain the above copyright notice, this list
 *    of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright notice, this
 *    list of conditions and the following disclaimer in the documentation and/or
 *    other materials provided with the distribution.
 *
 *    Neither the name of the copyright holder nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *  CONTRIBUTORS"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 *  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 *  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */

#include <unicode/ustdio.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#define IN_BRACKETS (1)
#define NOT_IN_BRACKETS (0)

int main()
{
	UFILE *fp_out, *fp_in;
	UChar32 c, c_status;
	unsigned char in_brackets = NOT_IN_BRACKETS;

	fp_out = u_finit(stdout, NULL, NULL);
	fp_in = u_finit(stdin, NULL, NULL);
	assert(fp_out != NULL);
	assert(fp_in != NULL);

	while ((c = u_fgetcx(fp_in)) != U_EOF) {
		assert(c != 0xFFFFFFFF); /* Fail if there was a malformed character. */
		switch(c) {
		case '<':
			in_brackets = IN_BRACKETS;
			break;
		case '>':
			in_brackets = NOT_IN_BRACKETS;

			/* Advance to the next line for readability. */
			c_status = u_fputc('\n', fp_out);
			assert(c_status != EOF);

			break;
		default:
			if (in_brackets == IN_BRACKETS) {
				c_status = u_fputc(c, fp_out);
				assert(c_status != EOF);
			}
			break;
		}
	}

	u_fclose(fp_out);
	u_fclose(fp_in);
	return 0;
}
