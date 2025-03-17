Artifact for the PLDI 2025 paper "Correctly Rounded Math Libraries Without Worrying about the Application’s Rounding Mode"
---

## Abstract:

We present the artifact for our PLDI 2025 paper, "Correctly Rounded
Math Libraries Without Worrying about the Application’s Rounding
Mode". We describe the list of claims made by the paper, the
installation instructions, and evaluation instructions. To ease the
installation effort, we provide a docker image with all required
software already installed.

---

## Table of Contents

1\. Hardware recommendation \
2\. Claims made in the paper \
3\. Installation Guide \
4\. Evaluation Guide for the Artifact \
(1) Check the correctness of OurLibm \
(2) Check the correctness of mainstream math libraries \
(3) Check the correctness of RLIBM with and without RNE (round-to-nearest-ties-to-even) \
(4) Check the performance of OurLibm against RLIBM \
(5) Instructions to Generate Functions with our Approach 

---

## Hardware recommendation

All of our evaluations were performed on an AMD EPYC 7313P machine with a 3.0GHz processor, which runs Ubuntu-24.04. However, we predict that the artifact should be functional with modern machines with 16GB of RAM, running Ubuntu-18.04 or later. For the ease of installation purposes, however, we recommend running the evaluation on Ubuntu-24.04. The docker image we provide also uses Ubuntu-24.04.

---

## Claims made in the paper

All claims to be evaluated in the artifact are found in Section 4 of the paper (i.e., Experimental Evaluation).

(1) Both our techniques (rounding-invariant input bounds and rounding-invariant outputs) successfully generate polynomials that produce correctly rounded results for all inputs in FP representations with up to 32-bits directly under all standard rounding modes (claimed in Table 1).

(2) Mainstream math libraries, on the other hand, do not produce correctly rounded results for all inputs, for all FP representations with up to 32-bits, and for all standard rounding modes, for several elementary functions (claimed in Table 1).

(3) When not running under RNE (round-to-nearest-ties-to-even), RLIBM does not produce correctly rounded results for all inputs, for all FP representations with up to 32-bits, and for all standard rounding modes, for several elementary functions (claimed in Table 1).

(4) On average, our functions are faster than RLIBM's implementations with explicit rounding mode setting via fegetround/fesetround (claimed in Figure 7).

---
## Installation Guide

We have pre-built a docker image and hosted it in the docker hub.

(1) Install docker if not already installed by following the installation documentation in this link: https://docs.docker.com/install/

We recommend installing docker and evaluating our artifact on a machine with Ubuntu. Although docker can be used with Windows or MacOS, docker may run on top of a linux VM.

(2) Download the pre-built docker image by using the command:
```
$ sudo docker pull spark0423/pldi2025artifact
```
The docker image is roughly 1.0GB

(3) Run the docker image:
```
$ sudo docker run -it spark0423/pldi2025artifact
```
(4) If running the docker image on macOS, increase docker's memory resource. You can increase memory resource by going to docker->preference->Resources. 12GB of memory usage should be more than enough.

(5) Installation is complete. Go to EVALUATION GUIDE section.

---

## Evaluation Guide

(1) Check the correctness of our library (Claim 1):

To test the correctness of our library, run the bash script,
```
$ ./CorrectnessTestOurLibm.sh
```
This script will take roughly 20 minutes. This script tests whether both the rounding-invariant input bounds and rounding-invariant outputs implementations in our library produce the correctly rounded results for uniformly sampled FP inputs with different number of exponent and mantissa bits under all standard rounding modes. If the test is successful, you should see "check" in green text, for each elementary function and representation for each method. Otherwise, it will print "incorrect" in red text, which signifies that the test has failed.

We also set up a test script to run this test for ALL possible FP inputs with bit-lengths <= 32. However, we really don't recommend running this for artifact evaluation purposes, as this will take > 24 hours, even when run in parallel...
```
$ ./CorrectnessTestFullOurLibm.sh
```
(2) Check the correctness of mainstream math libraries (Claim 2):

To test the correctness of mainstream math libraries (e.g., CORE-MATH and glibc), run the bash script,
```
$ ./CorrectnessTestOther.sh
```
This script will take roughly 20 minutes. The testing method is nearly identical to that for our library with the following difference: for functions for which the inputs with incorrect results are known, the inputs are included in the sample. This test corresponds to the columns for CORE-MATH and glibc in Table 1.

We also set up a test script to run this test for ALL possible FP inputs with bit-lengths <= 32. The test is expected to take over 24 hours.

```
$ ./CorrectnessTestFullOther.sh
```
(3) Check the correctness of RLIBM with and without RNE (round-to-nearest-ties-to-even) (Claim 3):

To test the correctness of RLIBM under various rounding modes, both without and without explicit rounding mode setting to RNE, run the bash script,
```
$ ./CorrectnessTestRLIBM.sh
```
This script will take roughly 20 minutes. The testing method is the same as that for CORE-MATH and glibc. To confirm the correctness of RLIBM's functions with respect to all inputs, representations (bit-lengths <= 32), and rounding modes, run the following script.

```
$ ./CorrectnessTestFullRLIBM.sh
```

As is the case with the other full-scale tests, the test is expected to take a prohibitively long time for artifact evaluation purposes.

(4) Check the performance of our library against RLIBM with rounding mode changes (Claim 4):

To test the speedup of both the rounding-invariant input bounds and outputs methods, run the bash script,
   
``` 
$ ./OverheadTest.sh
```
This script will take roughly 2 hours. For each function, this script executes three different implementations: rounding-invariant input bounds, rounding-invariant outputs, and RLIBM with the fesetround calls. The script executes each implementation on all binary32 FP inputs and collects the aggregate cycles. Once the script terminates, you will see the following file 'speedup_over_rlibm.pdf'. The file contains the contents of Figure 7.


## Generation of functions with our approach

We provide scripts to generate the oracle results for all our functions. For each function, we also provide scripts to generate intervals and polynomials using the three methods discussed in the paper: the default RLIBM method, the rounding-invariant outputs method, and the rounding-invariant input bounds method (see Interval and Polynomial Generation). We provide instructions to run the relevant scripts for each function.  

### Oracle Generation

(1) Generating the oracle for cos
```
$ cd full-gen/
$ ./CosOracle.sh
```
The oracle will be available in the file oracles/Cos34RNOOracle

(2) Generating the oracle for cosh
```
$ cd full-gen/
./CoshOracle.sh
```
The oracle will be available in the file oracles/Cosh34RNOOracle

(3) Generating the oracle for cospi

```
$ cd full-gen/
$ ./CospiOracle.sh
```
The oracle will be available in the file oracles/Cospi34RNOOracle

(4) Generating the oracle for exp

```
$ cd full-gen/
$ ./ExpOracle.sh
```
The oracle will be available in the file oracles/Exp34RNOOracle

(5) Generating the oracle for exp2

```
$ cd full-gen/
$ ./Exp2Oracle.sh
```
The oracle will be available in the file oracles/Exp234RNOOracle

(6) Generating the oracle for exp10

```
$ cd full-gen/
$ ./Exp10Oracle.sh
```
The oracle will be available in the file oracles/Exp1034RNOOracle

(7) Generating the oracle for log

```
cd full-gen/
./LogOracle.sh
```
The oracle will be available in the file oracles/Log34RNOOracle

(8) Generating the oracle for log2

```
$ cd full-gen/
$ ./Log2Oracle.sh
```
The oracle will be available in the file oracles/Log234RNOOracle

(9) Generating the oracle for log10

```
$ cd full-gen/
$ ./Log10Oracle.sh
```
The oracle will be available in the file oracles/Log1034RNOOracle

(10) Generating the oracle for sin

```
$ cd full-gen/
$ ./SinOracle.sh
```
The oracle will be available in the file oracles/Sin34RNOOracle

(11) Generating the oracle for sinh

```
$ cd full-gen/
$ ./SinhOracle.sh
```
The oracle will be available in the file oracles/Sinh34RNOOracle

(12) Generating the oracle for sinpi

```
$ cd full-gen/
$ ./SinpiOracle.sh
```
The oracle will be available in the file oracles/Sinpi34RNOOracle

### Interval and Polynomial Generation

(1) Generating intervals and polynomials for cos

(a) Original RLIBM method

To generate intervals for cos using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./CosSmallInterval.sh
$ ./Cos-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cos-RLIBM-Poly.sh
```
Upon completion, the coefficients of the five polynomials used for the RLIBM cos function will be available in the following files in the 'polynomials' directory: cos_small_rlibm_p1, cos_small_rlibm_p2, cossin_rlibm_p1, coscos_rlibm_p1, cossin_rlibm_p2, and coscos_rlibm_p2.

(b) Rounding-invariant outputs method

To generate intervals for cos using the rounding-invariant outputs method, run the following commands. Note that the script CosSmallInterval.sh only needs to be run once for cos since this specific interval generation process is not method dependent.

```
$ cd full-gen/
$ ./CosSmallInterval.sh
$ ./Cos-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cos-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the five polynomials used for the rounding-invariant outputs cos function will be available in the following files in the 'polynomials' directory: cos_small_ri_outputs_p1, cos_small_ri_outputs_p2, cossin_ri_outputs_p1, coscos_ri_outputs_p1, cossin_ri_outputs_p2, and coscos_ri_outputs_p2.

(c) Rounding-invariant input bounds method

To generate intervals for cos using the rounding-invariant input bounds method, run the following commands. Note that the script CosSmallInterval.sh only needs to be run once for cos since this specific interval generation process is not method dependent.

```
$ cd full-gen/
$ ./CosSmallInterval.sh
$ ./Cos-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cos-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the five polynomials used for the rounding-invariant input bounds cos function will be available in the following files in the 'polynomials' directory: cos_small_ri_inputs_p1, cos_small_ri_inputs_p2, cossin_ri_inputs_p1, coscos_ri_inputs_p1, cossin_ri_inputs_p2, and coscos_ri_inputs_p2.

(2) Generating intervals and polynomials for cosh\
(a) Original RLIBM method

To generate intervals for cosh using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Cosh-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cosh-RLIBM-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the RLIBM cosh function will be available in the following files in the 'polynomials' directory: coshcos_rlibm and coshsin_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for cosh using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Cosh-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cosh-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs cosh function will be available in the following files in the 'polynomials' directory: coshcos_ri_outputs and coshsin_ri_outputs.

(c) Rounding-invariant input bounds method

To generate intervals for cosh using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Cosh-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cosh-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds cosh function will be available in the following files in the 'polynomials' directory: coshcos_ri_inputs and coshsin_ri_inputs.

(3) Generating intervals and polynomials for cospi

(a) Original RLIBM method

To generate intervals for cospi using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Cospi-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cospi-RLIBM-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the RLIBM cospi function will be available in the following files in the 'polynomials' directory: cospicos_rlibm and cospisin_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for cospi using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Cospi-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cospi-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs cospi function will be available in the following files in the 'polynomials' directory: cospicos_ri_outputs and cospisin_ri_outputs.

(c) Rounding-invariant input bounds method

To generate intervals for cospi using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Cospi-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Cospi-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds cospi function will be available in the following files in the 'polynomials' directory: cospicos_ri_inputs and cospisin_ri_inputs.

(4) Generating intervals and polynomials for exp

(a) Original RLIBM method

To generate intervals for exp using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Exp-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp-RLIBM-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the RLIBM exp function will be available in the following files in the 'polynomials' directory: exp_rlibm_p1 and exp_rlibm_p2.

(b) Rounding-invariant outputs method

To generate intervals for exp using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Exp-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs exp function will be available in the following files in the 'polynomials' directory: exp_ri_outputs_p1 and exp_ri_outputs_p2.

(c) Rounding-invariant input bounds method

To generate intervals for exp using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Exp-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds exp function will be available in the following files in the 'polynomials' directory: exp_ri_inputs_p1 and exp_ri_inputs_p2.

(5) Generating intervals and polynomials for exp2

(a) Original RLIBM method

To generate intervals for exp2 using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Exp2-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp2-RLIBM-Poly.sh
```
Upon completion, the coefficients of the polynomial used for the RLIBM exp2 function will be available in the following files in the 'polynomials' directory: exp2_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for exp2 using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Exp2-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp2-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the polynomial used for the rounding-invariant outputs exp2 function will be available in the following file in the 'polynomials' directory: exp2_ri_outputs.

(c) Rounding-invariant input bounds method

To generate intervals for exp2 using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Exp2-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp2-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the the polynomial used for the rounding-invariant input bounds exp2 function will be available in the following files in the 'polynomials' directory: exp2_ri_inputs.

(6) Generating intervals and polynomials for exp10

(a) Original RLIBM method

To generate intervals for exp10 using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Exp10-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp10-RLIBM-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the RLIBM exp10 function will be available in the following files in the 'polynomials' directory: exp10_rlibm_p1 and exp10_rlibm_p2.

(b) Rounding-invariant outputs method

To generate intervals for exp10 using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Exp10-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp10-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs exp10 function will be available in the following files in the 'polynomials' directory: exp10_ri_outputs_p1 and exp10_ri_outputs_p2.

(c) Rounding-invariant input bounds method

To generate intervals for exp10 using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Exp10-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Exp10-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds exp10 function will be available in the following files in the 'polynomials' directory: exp10_ri_inputs_p1 and exp10_ri_inputs_p2.

(7) Generating intervals and polynomials for log

(a) Original RLIBM method

To generate intervals for log using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Log-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log-RLIBM-Poly.sh
```
Upon completion, the coefficients of the polynomial used for the RLIBM log function will be available in the following file in the 'polynomials' directory: log_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for log using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Log-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs log function will be available in the following files in the 'polynomials' directory: log_ri_outputs_p1 and log_ri_outputs_p2.

(c) Rounding-invariant input bounds method

To generate intervals for log using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Log-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds log function will be available in the following files in the 'polynomials' directory: log_ri_inputs_p1 and log_ri_inputs_p2.

(8) Generating intervals and polynomials for log2

(a) Original RLIBM method

To generate intervals for log2 using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Log2-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log2-RLIBM-Poly.sh
```
Upon completion, the coefficients of the polynomial used for the RLIBM log2 function will be available in the following files in the 'polynomials' directory: log2_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for log2 using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Log2-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log2-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the polynomial used for the rounding-invariant outputs log2 function will be available in the following file in the 'polynomials' directory: log2_ri_outputs.

(c) Rounding-invariant input bounds method

To generate intervals for log2 using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Log2-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log2-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the the polynomial used for the rounding-invariant input bounds log2 function will be available in the following files in the 'polynomials' directory: log2_ri_inputs.

(9) Generating intervals and polynomials for log10

(a) Original RLIBM method

To generate intervals for log10 using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Log10-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log10-RLIBM-Poly.sh
```
Upon completion, the coefficients of the polynomial used for the RLIBM log10 function will be available in the following file in the 'polynomials' directory: log10_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for log10 using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Log10-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log10-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs log10 function will be available in the following files in the 'polynomials' directory: log10_ri_outputs_p1 and log10_ri_outputs_p2.

(c) Rounding-invariant input bounds method

To generate intervals for log using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Log10-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Log10-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds log10 function will be available in the following files in the 'polynomials' directory: log10_ri_inputs_p1 and log10_ri_inputs_p2.


(10) Generating intervals and polynomials for sin

(a) Original RLIBM method

To generate intervals for sin using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./SinSmallInterval.sh
$ ./Sin-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sin-RLIBM-Poly.sh
```
Upon completion, the coefficients of the five polynomials used for the RLIBM sin function will be available in the following files in the 'polynomials' directory: sin_small_rlibm_p1, sin_small_rlibm_p2, sinsin_rlibm_p1, sincos_rlibm_p1, sinsin_rlibm_p2, and sincos_rlibm_p2.

(b) Rounding-invariant outputs method

To generate intervals for cos using the rounding-invariant outputs method, run the following commands. Note that the script SinSmallInterval.sh only needs to be run once for sin since this specific interval generation process is not method dependent.

```
$ cd full-gen/
$ ./SinSmallInterval.sh
$ ./Sin-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sin-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the five polynomials used for the rounding-invariant outputs sin function will be available in the following files in the 'polynomials' directory: sin_small_ri_outputs_p1, sin_small_ri_outputs_p2, sinsin_ri_outputs_p1, sincos_ri_outputs_p1, sinsin_ri_outputs_p2, and sincos_ri_outputs_p2.

(c) Rounding-invariant input bounds method

To generate intervals for cos using the rounding-invariant input bounds method, run the following commands. Note that the script SinSmallInterval.sh only needs to be run once for cos since this specific interval generation process is not method dependent.

```
$ cd full-gen/
$ ./SinSmallInterval.sh
$ ./Sin-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sin-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the five polynomials used for the rounding-invariant input bounds cos function will be available in the following files in the 'polynomials' directory: sin_small_ri_inputs_p1, sin_small_ri_inputs_p2, sinsin_ri_inputs_p1, sincos_ri_inputs_p1, sinsin_ri_inputs_p2, and sincos_ri_inputs_p2.

(11) Generating intervals and polynomials for sinh\
(a) Original RLIBM method

To generate intervals for sinh using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Sinh-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sinh-RLIBM-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the RLIBM sinh function will be available in the following files in the 'polynomials' directory: sinhcos_rlibm and sinhsin_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for sinh using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Sinh-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sinh-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs sinh function will be available in the following files in the 'polynomials' directory: sinhcos_ri_outputs and sinhsin_ri_outputs.

(c) Rounding-invariant input bounds method

To generate intervals for sinh using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Sinh-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sinh-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds sinh function will be available in the following files in the 'polynomials' directory: sinhcos_ri_inputs and sinhsin_ri_inputs.

(12) Generating intervals and polynomials for sinpi

(a) Original RLIBM method

To generate intervals for sinpi using the original RLIBM method, run the following commands.

```
$ cd full-gen/
$ ./Sinpi-RLIBM-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sinpi-RLIBM-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the RLIBM sinpi function will be available in the following files in the 'polynomials' directory: sinpicos_rlibm and sinpisin_rlibm.

(b) Rounding-invariant outputs method

To generate intervals for sinpi using the rounding-invariant outputs method, run the following commands.

```
$ cd full-gen/
$ ./Sinpi-RI-Outputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sinpi-RI-Outputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant outputs sinpi function will be available in the following files in the 'polynomials' directory: sinpicos_ri_outputs and sinpisin_ri_outputs.

(c) Rounding-invariant input bounds method

To generate intervals for sinpi using the rounding-invariant input bounds method, run the following commands.

```
$ cd full-gen/
$ ./Sinpi-RI-Inputs-Intervals.sh
```
After generating the intervals, run the following command in the full-gen directory for the polynomials.

```
$ ./Sinpi-RI-Inputs-Poly.sh
```
Upon completion, the coefficients of the two polynomials used for the rounding-invariant input bounds sinpi function will be available in the following files in the 'polynomials' directory: sinpicos_ri_inputs and sinpisin_ri_inputs.

