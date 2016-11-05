#ifndef KANN_H
#define KANN_H

#define KANN_VERSION "0.0"

#define KAD_LABEL_IN        1
#define KAD_LABEL_OUT_PRE   2
#define KAD_LABEL_OUT_TRUTH 3
#define KAD_LABEL_OUT_EST   4

#include <stdint.h>
#include "kautodiff.h"

typedef struct {
	float lr; // learning rate
	float fv; // fraction of validation data
	int mb_size; // size of a mini batch
	int epoch_lazy;
	int max_epoch;

	float decay;
} kann_mopt_t;

typedef struct {
	kad_rng_t rng; // for kautodiff, as it is independent of kann_rand
	int n;
	kad_node_t **v;
	kad_node_t *out_pre, *out_truth, *in; // these point to kann_t::v; they are not allocated
	kad_node_t *out_est;
	float *t, *g;
} kann_t;

#ifdef __cplusplus
extern "C" {
#endif

kann_t *kann_init(uint64_t seed);
void kann_destroy(kann_t *a);
void kann_sync(kann_t *a);
int kann_n_in(const kann_t *a);
int kann_n_out(const kann_t *a);
int kann_n_par(const kann_t *a);

void kann_write(const char *fn, const kann_t *ann);
kann_t *kann_read(const char *fn);

void kann_mopt_init(kann_mopt_t *mo);
void kann_train_fnn(const kann_mopt_t *mo, kann_t *a, int n, float **_x, float **_y);
const float *kann_apply_fnn1(kann_t *a, const float *x);

kann_t *kann_mlp_gen(int n_in, int n_out, int n_hidden_layers, int n_hidden_neurons, uint64_t seed);

#ifdef __cplusplus
}
#endif

#endif
