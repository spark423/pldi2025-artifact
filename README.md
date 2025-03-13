Correctly Rounded Math Libraries Without Worrying about the Application’s Rounding Mode #
---

Abstract:

We present the artifact for the accepted paper, Correctly Rounded Math Libraries Without Worrying about the Application’s Rounding Mode. We describe the list of claims made by the paper, the installation instructions, and evaluation instructions. To ease the installation effort, we provide a docker image with all required softwares installed already. 

---

Table of Content:

1\. Hardware recommendation \
2\. Claims made from the paper \
3\. Installation Guide \
4\. EVALUATION GUIDE FOR THE ARTIFACT \
(1) Check the correctness of OurLibm \
(2) Check the correctness of mainstream math libraries \
(3) Check the correctness of RLIBM with and without round-to-nearest-ties-to-even \
(4) Check the performance of OurLibm against RLIBM

---

1\. Hardware recommendation:

All of our evaluations were performed on an AMD EPYC 7313P machine with a 3.0GHz processor, which runs Ubuntu-24.04. However, we predict that the artifact should be functional with modern machines with 16GB of RAM, running Ubuntu-18.04 or later. For the ease of installation purposes, however, we recommend running the evaluation on Ubuntu-24.04. The docker image we provide also uses Ubuntu-24.04.

---

2\. Claims made from the paper:

All claims to be evaluated in the artifact are found in Section 4. Experimental Evaluation.

(1) Both our techniques (rounding-invariant input bounds and rounding-invariant outputs) successfully generate polynomials that produce correctly rounded results for all inputs in FP representations with up to 32-bits directly under all standard rounding modes (claimed in Table 1).

(2) Mainstream math libraries, on the other hand, do not produce correctly rounded results for all inputs, for all FP representations with up to 32-bits, and for all standard rounding modes, for several elementary functions (claimed in Table 1).

(3) When not running under RNE (round-to-nearest-ties-to-even), RLIBM does not produce correctly rounded results for all inputs, for all FP representations with up to 32-bits, and for all standard rounding modes, for several elementary functions (claimed in Table 1).

(4) On average, OurLibm functions are faster than RLIBM's implementations with explicit rounding mode setitng via fegetround/fesetround (claimed in Figure 7).

---
3\. Installation guide:

We have prebuilt a docker image and hosted it in the docker hub.

(1) Install docker if not already installed by following the installation documentation in this link: https://docs.docker.com/install/

We recommend installing docker and evaluating our artifact on a machine with Ubuntu. Although docker can be used with Windows or MacOS, docker may run on top of a linux VM.

(2) Download the prebuilt docker image by using the command:
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

4\. EVALUATION GUIDE:

(1) Check the correctness of OurLibm (Claim 1):

To test the correctness of OurLibm, run the bash script,
```
$ ./CorrectnessTestOurLibm.sh
```
This script will take roughly 20 minutes. This script tests whether both the rounding-invariant input bounds and rounding-invariant outputs implementations in OurLibm produce the correctly rounded results for uniformly sampled FP inputs with different number of exponent and mantissa bits under all standard rounding modes. If the test is successful, you should see "check" in green text, for each elementary function and representation for each method. Otherwise, it will print "incorrect" in red text, which signifies that the test has failed.

We also set up a test script to run this test for ALL possible FP inputs with bit-lengths <= 32. However, we really don't recommend running this for artifact evaluation purposes, as this will take > 48 hours, even when run in parallel...
```
$ ./CorrectnessTestFullOurLibm.sh
```
(2) Check the correctness of mainstream math libraries (Claim 2):

To test the correctness of mainstream math libraries (e.g., CORE-MATH and glibc), run the bash script,
```
$ ./CorrectnessTestOther.sh
```
This script will take roughly 20 minutes. The testing method is the same as that for OurLibm. This test corresponds to the columns for CORE-MATH and glibc in Table 1.

We also set up a test script to run this test for ALL possible FP inputs with bit-lengths <= 32. As is the case with the test for OurLibm, the test is expected to take a prohibitively long time.

```
$ ./CorrectnessTestFullOther.sh
```
(3) Check the correctness of RLIBM with and without round-to-nearest-ties-to-even (Claim 3):


(4) Check the performance of OurLibm against RLIBM (Claim 4):

To test the speedup of both the rounding-invariant input bounds and outputs methods, run the bash script,
   
``` 
$ ./OverheadTest.sh
```
This script will take roughly 2 hours. For each function, this script executes three different implementations: rounding-invariant input bounds, rounding-invariant outputs, and RLIBM with the fesetround calls. The script executes each implementation on all binary32 FP inputs and collects the aggregate cycles. Once the script terminates, you will see the following file 'speeup_over_rlibm.pdf'. The file contains the contents of Figure 7.


