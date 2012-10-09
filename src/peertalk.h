#ifndef PEERTALK_H
#define PEERTALK_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

//C interface if used as a library
typedef void * peertalk_ref_t;

/**
 Create a new peertalk reference
 *
 @discussion The reference must be freed using peertalk_free
 *
 @return A new peertalk reference
 *
 @see peertalk_free(peertalk_ref_t pt)
 */
peertalk_ref_t peertalk_create();

/**
 Frees a peertalk reference created with peertalk_create()
 *
 @see peertalk_create()
 */
void peertalk_free(peertalk_ref_t pt);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PEERTALK_H