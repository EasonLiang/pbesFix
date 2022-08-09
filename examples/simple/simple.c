#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"

int main()
{
    uint8_t buffer[128];
    size_t  message_length;
    {
	SimpleMessage message = SimpleMessage_init_zero;
	pb_ostream_t oStream = pb_ostream_from_buffer(buffer,sizeof(buffer));
	message.lucky_number = 13;
	if(!pb_encode(&oStream,SimpleMessage_fields, &message)) {
		printf("Encoding failed: %s\n",PB_GET_ERROR(&oStream));	
		return 1;
	}
	message_length = oStream.bytes_written;
    }

    {
	SimpleMessage message = SimpleMessage_init_zero;
	pb_istream_t iStream = pb_istream_from_buffer(buffer,message_length);
	if(!pb_decode(&iStream,SimpleMessage_fields,&message)) {
		printf("Decoding failed: %s\n",PB_GET_ERROR(&iStream));
		return 1;
	} else {
		printf("Your lucky number was %d\n",message.lucky_number);
	}
    }
}
