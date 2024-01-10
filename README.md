# AAC-Clydespace Avionics Software Challenge
You are given the LIS3MDLTR 3-Axis Magnetometer sensor. The data sheet is
located at `doc/lism3mdl.pdf`

## Task Description
You must use the C API defined in `i2c.h` to operate on an I2C bus.

We provide example stub implementations of this API in `i2c.c`. You are free to
extend the provided stub functions for the API.

Please write a device driver that implements the following API:
- Get the full-scale configuration
- Get and set the output data rate
- Enable or disable the interrupt pin
- Read the output data of a specified axis

## Development
You are provided this minimal repository, `aac-code-challenge`, please perform
your work on branch `<candidate_name>`

Documentation can be found in `aac-code-challenge/doc`

Once complete, please repackage and email back this repo to your interviewers

## Scope
You shouldn't need to spend more than a couple of hours on the task.

This is not a closed book assessment.

## Extra Thoughts
If you have time, answer the following questions:
- What changes you would make to this interfaces for use in an RTOS
environment?
- How might the I2C API be improved
