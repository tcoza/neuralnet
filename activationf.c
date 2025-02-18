#include <random.h>

static double logistic_f(double x) { return 1 / (exp(-x) + 1); }
static double logistic_df(double x) { double t = logistic_f(x); return t * (1 - t); }
static void logistic_initLayer(Layer *layer)
{
	for (int i = 0; i < layer->weights->height; i++)
	{
		for (int j = 0; j < layer->weights->width; j++)
			matrix_set(layer->weights, i, j, 3 * uniform(-1,+1) / layer->weights->width);
		matrix_set(layer->biases, i, 0, gaussian(0, 2));
	}
}

static double relu01_df(double x) { return (x > 0) ? 1 : 0.01; }
static double relu01_f(double x) { return x * relu01_df(x);  }
static void relu01_initLayer(Layer *layer)
{
	for (int i = 0; i < layer->weights->height; i++)
	{
		for (int j = 0; j < layer->weights->width; j++)
			matrix_set(layer->weights, i, j, 2 * random01() / layer->weights->width);
		matrix_set(layer->biases, i, 0, gaussian(0, 1));
	}
}

static ActivationFunction activationFunctions[] =
{
	{ .type = LOGISTIC, .f = logistic_f, .df = logistic_df, .initLayer = logistic_initLayer },
	{ .type = RELU_01, .f = relu01_f, .df = relu01_df, .initLayer = relu01_initLayer }
};
