#include <Python.h>
#include <math.h>

static PyObject *factorize(PyObject *self, PyObject *args)
{
    unsigned long n;
    if (!PyArg_ParseTuple(args, "k", &n))
        return NULL;

    PyObject *result = PyList_New(0);
    for (unsigned long i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            PyObject *factorization = Py_BuildValue("(kk)", i, n / i);
            PyList_Append(result, factorization);
            Py_DECREF(factorization);
            break;
        }
    }

    return result;
}

static PyMethodDef FactorizeMethods[] = {
    {"factorize", factorize, METH_VARARGS, "Factorize a number into a product of two smaller numbers."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef factorizemodule = {
    PyModuleDef_HEAD_INIT,
    "factorize",
    NULL,
    -1,
    FactorizeMethods
};

PyMODINIT_FUNC PyInit_factorize(void)
{
    return PyModule_Create(&factorizemodule);
}

