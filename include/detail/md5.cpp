	

#include "md5.h"



/**
 * @Construct a MD5 object with a string.
 *
 * @param {message} the message will be transformed.
 *
 */
/**
 * @Generate md5 digest.
 *
 * @return the message-digest.
 *
 */
const byte* MD5::getDigest() 

/**
 * @Initialization the md5 object, processing another message block,
 * and updating the context.
 *
 * @param {input} the input message.
 *
 * @param {len} the number btye of message.
 *
 */
void MD5::init(const byte* input, size_t len) 

/**
 * @MD5 basic transformation. Transforms state based on block.
 *
 * @param {block} the message block.
 */
void MD5::transform(const byte block[64]) 

/**
* @Encodes input (unsigned long) into output (byte).
*
* @param {input} usigned long.
*
* @param {output} byte.
*
* @param {length} the length of input.
*
*/
void MD5::encode(const bit32* input, byte* output, size_t length)


/**
 * @Decodes input (byte) into output (usigned long).
 *
 * @param {input} bytes.
 *
 * @param {output} unsigned long.
 *
 * @param {length} the length of input.
 *
 */
void MD5::decode(const byte* input, bit32* output, size_t length)



/**
 * @Convert digest to string value.
 *
 * @return the hex string of digest.
 *
 */
string MD5::toStr() 

