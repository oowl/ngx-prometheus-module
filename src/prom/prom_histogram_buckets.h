
#include "stdlib.h"
#include "prom_metric.h"

#ifndef PROM_HISTOGRAM_BUCKETS_H
#define PROM_HISTOGRAM_BUCKETS_H

typedef struct prom_histogram_buckets {
  int count;                  /**< Number of buckets */
  const double *upper_bounds; /**< The bucket values */
  ngx_slab_pool_t *shpool; 
} prom_histogram_buckets_t;

/**
 * @brief Construct a prom_histogram_buckets_t*
 * @param count The number of buckets
 * @param bucket The first bucket. A variable number of bucket values may be passed. This quantity MUST equal the value
 *               passed as count.
 * @return The constructed prom_histogram_buckets_t*
 */
prom_histogram_buckets_t *prom_histogram_buckets_new(ngx_slab_pool_t *shpool, size_t count, double bucket, ...);

/**
 * @brief the default histogram buckets: .005, .01, .025, .05, .1, .25, .5, 1, 2.5, 5, 10
 */
extern prom_histogram_buckets_t *prom_histogram_default_buckets;

/**
 *@brief Construct a linearly sized prom_histogram_buckets_t*
 * @param start The first inclusive upper bound
 * @param width The distance between each upper bound
 * @param count The total number of buckets. The final +Inf bucket is not counted and not included.
 * @return The constructed prom_histogram_buckets_t*
 */
prom_histogram_buckets_t *prom_histogram_buckets_linear(double start, double width, size_t count);

/**
 * @brief Construct an exponentially sized prom_histogram_buckets_t*
 * @param start The first inclusive upper bound. The value MUST be greater than 0.
 * @param factor The factor to apply to the previous upper bound to produce the next upper bound. The value MUST be
 *                greater than 1.
 * @param count The total number of buckets. The final +Inf bucket is not counted and not included. The value MUST be
 *              greater than or equal to 1
 * @return The constructed prom_histogram_buckets_t*
 */
prom_histogram_buckets_t *prom_histogram_buckets_exponential(double start, double factor, size_t count);

/**
 * @brief Destroy a prom_histogram_buckets_t*. Self MUST be set to NULL after destruction. Returns a non-zero integer
 *        value upon failure.
 * @param self The target prom_histogram_buckets_t*
 * @return Non-zero integer value upon failure
 */
int prom_histogram_buckets_destroy(prom_histogram_buckets_t *self);

/**
 * @brief Get the count of buckets
 * @param self The target prom_histogram_buckets_t*
 * @return The count of buckets
 */
size_t prom_histogram_buckets_count(prom_histogram_buckets_t *self);

#endif  // PROM_HISTOGRAM_BUCKETS_H