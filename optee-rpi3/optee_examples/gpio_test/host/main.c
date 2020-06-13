/*
 * Copyright (c) 2016, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <err.h>
#include <stdio.h>
#include <string.h>

/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

#define GPIO_SERVICE_UUID \	
		{ 0x9ca510b1, 0x0903, 0x4b3b, \	
			{ 0x92, 0xa9, 0x16, 0xba, 0x34, 0x22, 0x28, 0xf1 } }	
#define GPIO_ON             0
#define GPIO_OFF            1
#define TEST_PSEUDO_TA      2

int main(void)
{
	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_Operation op;
	TEEC_UUID uuid = GPIO_SERVICE_UUID;
	uint32_t err_origin;

	/* Initialize a context connecting us to the TEE */
	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);

	/*
	 * Open a session to the "rpi3_gpio18" pseudo TA, the TA will print
	 */
	res = TEEC_OpenSession(&ctx, &sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, err_origin);

	/*
	 * Execute a function in the TA by invoking it
	 *
	 * The value of command ID part and how the parameters are
	 * interpreted is part of the interface provided by the TA.
	 */

	/* Clear the TEEC_Operation struct */
	memset(&op, 0, sizeof(op));

	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */
	op.paramTypes = TEEC_PARAM_TYPES(
			TEEC_VALUE_OUTPUT, 
			TEEC_NONE,
			TEEC_NONE, 
			TEEC_NONE);

	/*
	 * TA_HELLO_WORLD_CMD_INC_VALUE is the actual function in the TA to be
	 * called.
	 */
	printf("Invoking Test %d\n", op.params[0].value.a);
	res = TEEC_InvokeCommand(&sess, TEST_PSEUDO_TA, &op,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, 
		"TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
		res, err_origin);
	printf("TA Test was successful %d\n", op.params[0].value.a);
		
	/* Clear the TEEC_Operation struct */
	memset(&op, 0, sizeof(op));

	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */
	op.paramTypes = TEEC_PARAM_TYPES(
			TEEC_VALUE_INPUT, 
			TEEC_NONE,
			TEEC_NONE, 
			TEEC_NONE);
	
	printf("Invoking GPIO ON %d\n", op.params[0].value.a);
	res = TEEC_InvokeCommand(&sess, GPIO_ON, &op,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, 
		"TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
		res, err_origin);
	printf("TA successfully invoked GPIO ON%d\n", op.params[0].value.a);
		
	/* Clear the TEEC_Operation struct */
	memset(&op, 0, sizeof(op));

	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */
	op.paramTypes = TEEC_PARAM_TYPES(
			TEEC_VALUE_INPUT, 
			TEEC_NONE,
			TEEC_NONE, 
			TEEC_NONE);
	
	printf("Invoking GPIO OFF %d\n", op.params[0].value.a);
	res = TEEC_InvokeCommand(&sess, GPIO_OFF, &op,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, 
		"TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
		res, err_origin);
	printf("TA successfully invoked GPIO OFF%d\n", op.params[0].value.a);

	/*
	 * We're done with the TA, close the session and
	 * destroy the context.
	 *
	 * The TA will print "Goodbye!" in the log when the
	 * session is closed.
	 */

	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);

	return 0;
}
