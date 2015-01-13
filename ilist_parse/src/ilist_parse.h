#include <stdlib.h>

typedef unsigned int uint32;

/**
 * This function parses the input c string str into integer vector.
 *
 * @param int_vec  [out] Parsed integers are saved into this vector on
 *                       the heap, it should be free by caller after using.
 * @param vec_size [out] Integer vector size is saved in it.
 * @param str      [in]  Input integer list string. The valid input should
 *                       be composed of digit/ comma only. The integers
 *                       are separated by comma. Its regular expression is:
 *                       (\s)*(+|-)?([0-9])+(\s)*(,(\s)*(+|-)?([0-9])+(\s)*)*
 *
 * @return 0 if the string is parsed into vector successfully.
 *         -1 indicates invalid input arguments.
 *         -2 indicates OOM happens in parsing process.
 */
int parse_ilist_str(int **int_vec, uint32 *vec_size, const char *str);
