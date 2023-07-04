#include <Python.h>
#include <stdio.h>

/* Factorize a number n into a product of two smaller numbers */
void factorize(PyObject *n_obj) {
    PyLongObject *n = (PyLong_Object *)n_obj;
    long i;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            PyObject *p_obj = PyLong_FromLong(i);
            PyObject *q_obj = PyLong_FromLong(n / i);
            PyObject *result = PyUnicode_FromFormat("%ld=%ld*%ld", n, i, n / i);
            if (!p_obj || !q_obj || !result) {
                Py_DECREF(p_obj);
                Py_DECREF(q_obj);
                Py_XDECREF(result);
                return;
            }
            printf("%s\n", PyUnicode_AsUTF8(result));
            Py_DECREF(p_obj);
            Py_DECREF(q_obj);
            Py_DECREF(result);
            return;
        }
    }
}
