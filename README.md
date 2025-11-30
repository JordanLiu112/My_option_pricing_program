# My_option_pricing_program
This homework folder contains all my work related to the option pricing program that I had to design and submit in Week 9 of my online course, C++ Programming for Financial Engineering.
Read the Microwoft Word document "Jordan Liu - Level 9 Group A and B" for a complete overview of how I programmed the option pricer. I have copy and pasted this document below:

Jordan Liu 
Groups A and B – Exact Pricing Methods

Assignment tasks:
• You will need to encapsulate all functionality (i.e., option pricing, greeks, matrix pricing) into proper classes. You should submit Group A and Group B as a single, comprehensive project that takes all described functionality into account, and presents a unified, well-structured, robust, and flexible design. While you have full discretion to make specific design decisions in this level, your grade for Groups A and B will be based on the overall quality of the submitted code in regards to robustness, flexibility, clarity, code commenting, efficiency, conciseness, taking previously-learned concepts into account, and correctness.
 • Your single main() function should fully test each and every aspect of your option pricing classes, to ensure correctness prior to submission. This is of utmost importance. 
• All answers to questions, as well as batch test outputs should be outlined in a document. Additionally, and justifications for design decisions should be outlined in the document as well.

Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628). 
Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557). 
Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326). 
Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).

For Group A part a), I created a class “BlackScholes” that has six double data members (for asset price S, strike price K, etc.) and public functions that return the call and put prices using the formulas provided. To help make the put function, I created private functions d1(), d2(), and N(x) to calculate the values for d1, d2, and the standard cumulative normal distribution. The class is declared in BlackScholes.h and defined in BlackScholes.cpp. 
For part b), I expanded the BlackScholes class’ call and put functions, so that they could return the call price given the put price or the put price given the call price. I also created a new function “verifyParity” that checked if put and call prices satisfied put-call parity. 
For part c), I first created the global makeMesh function that takes a start value, an end value, and a step value in order to return a mesh array of S values. I declared makeMesh in HelperFunctions.h and defined it in HelperFunctions.cpp; I also created some print functions (e.g. printBatch) in the HelperFunction files to simplify the process of printing results in Main.cpp. Then, I expanded the call and put functions in BlackScholes so that they could take a vector of S values and return a vector of call or put prices. Finally, I created a printMesh function in HelperFunctions. 
For part d), I extended part c) and created callMatrix and putMatrix functions in BlackScholes that can take two vectors, one of which is of S values and the other is of any other parameter, and return a matrix of prices. For the functions to work, I added a string argument to identify what the second parameter is. Then, I created a printMatrix function and defined It in Helperfunctions.cpp to see the matrix output.  To make the process of creating a matrix input easier in Main.cpp, I also added a makeMeshPair function which is just a slightly reworked version of makeMesh. 
For option sensitivities, I declared the necessary public functions like callDelta(), putDelta(), gamma(), etc. in BlackScholes.h and added another private function n(x) to calculate the standard Normal pdf; this made it easier to construct the option sensitivities formulae in BlackScholes.cpp. For callTheta() and putTheta(), I constructed each term in the formulae (shown in comments) and then combined all the terms together in a single “return” line. Then, I created another helper function called “printGreeks”. Unlike the other print helper functions, this one took a const BlackScholes& argument and an integer argument to specify the batch number; then, it calculates and prints all the option sensitivities for the batch. I thought of modifying printMatrix and printBatch to take a const BlackScholes& argument, but decided against it; this would have made those functions less flexible, since they would only be able to use one set of functions (e.g. calculating prices from the call and put formulae) and not any other (e.g. calculating the call and put prices based on put-call parity). Furthermore, I saw that printMesh flexibility would be very useful for the next exercise in b).
Part b) was relatively easy: I just had to expand callDelta and putDelta so they could accept and return a vector of doubles; then I copied the code I already made for the vector versions of callPrice and putPrice. In that code, I swapped out callPrice and putPrice with callDelta and putDelta. I used makeMesh to generate a new vector of S values appropriate for batch 5 and then used printMesh to print the results. 
For part c), I adjusted the code for callMatrix and putMatrix so that they received a string argument to specify what output type was wanted: gamma, delta, or price. Then, I added a simple if-else statement to the matrix function definitions. I also created another helper function, printMatrixPair, specifically for printing matrices of parameters; printMatrix accepts only matrices of doubles and so it does not work on my parameter matrices, which are matrices of pairs of strings and doubles. I also made some formatting improvements to printMatrix and printMatrixPair. 
For part d), I expanded the code for callDelta, putDelta, gamma so that they could receive a double argument (h). Then, I changed the value assigned to the S data member to S+h and ran callPrice() to get V(S+h). I repeated this process to get the value of V(S-h), reset the S data member to its original value, and then returned the divided difference delta. For gamma, I also needed to get the value of V(S), so I just ran callPrice() with the S data member set to its original value. Expanding the code for S-value vectors was easy – it was simply a matter of declaring a callDelta function that received a vector of doubles and a double (h) and returned a vector of doubles; then I copied my previous code for the callDelta() vector function and added an “h” to callPrice when it was called in the for loop. I repeated this process for putDelta and gamma vector functions too. To compare the divided difference (DD) approximations with the exact deltas, I created another helper function called “printCompare” that received a vector of S values, a BlackScholes& batch, and a double for h. This function creates the exact delta call vector and the DD-approximated vector; then, it prints them in columns alongside columns of their respective S-values and the difference between the exact value and the DD estimate. It repeats this process for delta put and gamma. 
For Group B part a), I added callPriceUS and putPriceUS to the BlackScholes class in order to calculate the US perpetual prices. I also created two more private functions, y1() and y2(), to help me implement the formulae for the US perpetuals. Then, I created “batch 6” using the data set provided in part b) and tested the functions with printBatch. Since I already had a 5-argument BlackScholes constructor,  I had to use the 6-argument constructor to make batch 6 and set T=0; T doesn’t appear in the formulae for US perpetuals anyways, so its value does not really matter. For part c), I copied my code for the vector call and put functions, substituted callPriceUS and putPriceUS for callPrice and putPrice, and then used makeMesh and printMesh in Main.cpp. Part d) simply involved me inserting another else-if line to the callMatrix and putMatrix functions: if the string argument reads “perpetual”, then the function uses callPriceUS (or putPriceUS) and pushes the result into the vector of option prices. In Main.cpp, I created some more vectors of parameter-value pairs, combined them into a parameter matrix, and printed out the corresponding matrices of US perpetual option prices; the flexibility of my helper functions was very useful, since I could use printMatrix and printMatrixPair again. 
Some notes on design – although the worksheet suggests testing a vector with fifty S-values as an example, I created smaller vectors with ten S-values each so that printing the output wouldn’t take too much space. That said, my code can still work with larger vectors, and it would only take some minor adjustments to the start and end values in the makeMesh() functions in Main.cpp for my program to use a vector with fifty S-values. The worksheet also suggests creating multiple classes for option pricing, greeks, matrix pricing, etc. But I was able to encapsulate all functionality into the BlackScholes class. It would be easy to divide up the code in the BlackScholes class into separate classes for option pricing, greeks, and matrix pricing, but I did not think it was necessary. 

Update (2025 July 24): in response to tutor A. Palley’s comments, I redid the matrix pricer so that it could receive a generic matrix of option parameters and generate a vector of option prices or deltas. I also implemented his suggestions to divide up the BlackScholes class into several derived classes in the way he specified. This allows for a much more flexible implementation. 

The batch test outputs are on the next page:
 
***Group A - Implement the formulae for call and put option pricing.

The output should read:
Batch 1: C = 2.13337, P = 5.84628
Batch 2 : C = 7.96557, P = 7.96557
Batch 3 : C = 0.204058, P = 4.07326
Batch 4 : C = 92.17570, P = 1.24750

Output:
Batch 1: C = 2.13337, P = 5.84628
Batch 2: C = 7.96557, P = 7.96557
Batch 3: C = 0.204058, P = 4.07326
Batch 4: C = 92.1757, P = 1.2475

***Group A - Apply the put-call parity relationship to compute call and put option prices

Batch 1: C = 2.13337, P = 5.84628
Batch 2: C = 7.96557, P = 7.96557
Batch 3: C = 0.204056, P = 4.07326
Batch 4: C = 92.1757, P = 1.2475

(Notice the very slight rounding error for batch 3 when we compute its call price from its put price)

The call price 2.13337 and put price 5.84628 do satisfy put-call parity
The call price 7.96557 and put price 7.96557 do satisfy put-call parity
The call price 0.204058 and put price 4.07326 do satisfy put-call parity
The call price 92.1757 and put price 1.2475 do satisfy put-call parity

***Group A - Compute option prices for a monotonically increasing range of underlying values of S

For Batch 1:
S       Call prices     Put prices
--------------------------------
45       0.0278174      18.7407
46       0.0429083      17.7558
47       0.0644467      16.7774
48       0.0944125      15.8073
49        0.135117      14.848
50        0.189181      13.9021
51        0.259494      12.9724
52        0.349151      12.0621
53        0.461376      11.1743
54        0.599432      10.3123
55         0.76652      9.47943

***Group A - Extend part c) so we can input a matrix of option parameters (e.g. S and T) and receive a matrix of option prices

Parameter matrix:

         S:     60         K:     65         T:   0.25         r:   0.08       sig:    0.3         b:   0.08
         S:    100         K:    100         T:      1         r:      0       sig:    0.2         b:      0
         S:      5         K:     10         T:      1         r:   0.12       sig:    0.5         b:   0.12
         S:    100         K:    100         T:     30         r:   0.08       sig:    0.3         b:   0.08

Call prices:

Option 1: 2.13337
Option 2: 7.96557
Option 3: 0.204058
Option 4: 92.1757

Put prices:

Option 1: 5.84628
Option 2: 7.96557
Option 3: 4.07326
Option 4: 1.2475

***Group A - Implement the formulae for option sensitivities with specified data set ('Batch 5')
Batch 5: S = 105, K = 100, T = 0.5, r = 0.1, sig = 0.36, b = 0
The output should show delta call = 0.5946, delta put = -0.3566

Option sensitivites of Batch 5:
Call delta: 0.594629
Put delta: -0.356601
Gamma: 0.0134936
Vega: 26.7781
Call theta: -8.39684
Put theta: -8.87245

***Group A - compute call delta price for a monotonically increasing range of underlying values of S

For Batch 5:
S       Call prices     Put prices
--------------------------------
100       0.523785      -0.427444
101       0.538459      -0.412771
102       0.552894      -0.398335
103       0.567076      -0.384153
104       0.580992      -0.370237
105       0.594629      -0.356601
106       0.607976      -0.343253
107       0.621025      -0.330205
108       0.633767      -0.317463
109       0.646196      -0.305034
110       0.658306      -0.292923

***Group A - adjust matrix code to accept a matrix of option parameters and return a mesh of Delta or Gamma

Parameter matrix:
         S:     60         K:     65         T:   0.25         r:   0.08       sig:    0.3         b:   0.08
         S:    100         K:    100         T:      1         r:      0       sig:    0.2         b:      0
         S:      5         K:     10         T:      1         r:   0.12       sig:    0.5         b:   0.12
         S:    100         K:    100         T:     30         r:   0.08       sig:    0.3         b:   0.08
         S:    105         T:    0.5

The corresponding call deltas for the parameter matrix, applied to batch 5, is:

Option 1: 0.372483
Option 2: 0.539828
Option 3: 0.185048
Option 4: 0.988761
Option 5: 0.594629

The corresponding call gammas for the parameter matrix, applied to batch 5, is:

Option 1: 0.0420428
Option 2: 0.0198476
Option 3: 0.106789
Option 4: 0.000179578
Option 5: 0.0134936

The corresponding put deltas for the parameter matrix, applied to batch 5, is:

Option 1: -0.627517
Option 2: -0.460172
Option 3: -0.814952
Option 4: -0.0112394
Option 5: -0.356601

The corresponding put gammas for the parameter matrix, applied to batch 5, is:

Option 1: 0.0420428
Option 2: 0.0198476
Option 3: 0.106789
Option 4: 0.000179578
Option 5: 0.0134936

***Group A - Use divided differences to approximate option sensitivities

Call deltas (h = 0.01):
  S          Exact        Approx.     Difference
----------------------------------------------------
100       0.523785       0.523785    3.69656e-09
101       0.538459       0.538459    3.97157e-09
102       0.552894       0.552894     4.2217e-09
103       0.567076       0.567076     4.4473e-09
104       0.580992       0.580992    4.64776e-09
105       0.594629       0.594629     4.8249e-09
106       0.607976       0.607976    4.97904e-09
107       0.621025       0.621025     5.1098e-09
108       0.633767       0.633767    5.21945e-09
109       0.646196       0.646196    5.30979e-09
110       0.658306       0.658306    5.37882e-09

Put deltas (h = 0.01):
  S          Exact        Approx.     Difference
----------------------------------------------------
100      -0.427444      -0.427444    3.69716e-09
101      -0.412771      -0.412771    3.97289e-09
102      -0.398335      -0.398335    4.22195e-09
103      -0.384153      -0.384153    4.44755e-09
104      -0.370237      -0.370237    4.64837e-09
105      -0.356601      -0.356601    4.82622e-09
106      -0.343253      -0.343253     4.9793e-09
107      -0.330205      -0.330205    5.11076e-09
108      -0.317463      -0.317463    5.22041e-09
109      -0.305034      -0.305034    5.30933e-09
110      -0.292923      -0.292923    5.37942e-09

Gammas (h = 0.01):
  S          Exact        Approx.     Difference
----------------------------------------------------
100      0.0147873      0.0147873   -9.43837e-11
101      0.0145571      0.0145571    9.26783e-11
102      0.0143112      0.0143112   -1.08068e-10
103       0.014051       0.014051    1.57078e-10
104       0.013778       0.013778    1.24025e-10
105      0.0134936      0.0134936   -1.01516e-10
106      0.0131994      0.0131994   -1.72245e-11
107      0.0128966      0.0128966    8.83819e-11
108      0.0125865      0.0125865     4.1616e-11
109      0.0122705      0.0122705    2.54542e-10
110      0.0119498      0.0119498   -6.09839e-11

Now let's set h = 5 and see how this worsens the approximations

Call deltas (h = 5):
  S          Exact        Approx.     Difference
----------------------------------------------------
100       0.523785       0.522869    0.000916338
101       0.538459       0.537474    0.000985198
102       0.552894       0.551846     0.00104782
103       0.567076       0.565972     0.00110428
104       0.580992       0.579837     0.00115467
105       0.594629        0.59343     0.00119913
106       0.607976       0.606738     0.00123782
107       0.621025       0.619754     0.00127092
108       0.633767       0.632468     0.00129865
109       0.646196       0.644874     0.00132123
110       0.658306       0.656967     0.00133888

Put deltas (h = 5):
  S          Exact        Approx.     Difference
----------------------------------------------------
100      -0.427444      -0.428361    0.000916338
101      -0.412771      -0.413756    0.000985198
102      -0.398335      -0.399383     0.00104782
103      -0.384153      -0.385257     0.00110428
104      -0.370237      -0.371392     0.00115467
105      -0.356601        -0.3578     0.00119913
106      -0.343253      -0.344491     0.00123782
107      -0.330205      -0.331476     0.00127092
108      -0.317463      -0.318761     0.00129865
109      -0.305034      -0.306355     0.00132123
110      -0.292923      -0.294262     0.00133888

Gammas (h = 5):
  S          Exact        Approx.     Difference
----------------------------------------------------
100      0.0147873      0.0147513    3.59937e-05
101      0.0145571      0.0145243    3.28564e-05
102      0.0143112      0.0142814    2.97444e-05
103       0.014051      0.0140243    2.66763e-05
104       0.013778      0.0137543    2.36687e-05
105      0.0134936      0.0134729    2.07363e-05
106      0.0131994      0.0131815    1.78918e-05
107      0.0128966      0.0128814    1.51461e-05
108      0.0125865       0.012574    1.25083e-05
109      0.0122705      0.0122605    9.98603e-06
110      0.0119498      0.0119422    7.58515e-06

***Group B - Program the formulae for American perpetual options

Output for batch 6 (S = 110, K = 100, r = 0.1, sig = 0.1, b = 0.02) should read C = 18.5035, P = 3.03106

Batch 6: C = 18.5035, P = 3.03106

***Group B - compute US perpetual option prices for a monotonically increasing range of values of S

S       Call prices     Put prices
--------------------------------
105        15.9316      4.04761
106        16.4249      3.81598
107        16.9286      3.5996
108        17.4429      3.39733
109        17.9678      3.20813
110        18.5035      3.03106
111        19.0501      2.86523
112        19.6078      2.70985
113        20.1765      2.56416
114        20.7566      2.42748
115        21.3481      2.29919

***Group B - input a matrix of option parameters and receive a mesh of Perpetual American option prices

Parameter matrix:
         S:    110         K:    100         r:    0.1       sig:    0.1         b:   0.02
         S:    110         K:    100         T:      0         r:    0.1       sig:    0.1         b:   0.02
         S:    100         K:     90         r:   0.12
       sig:   0.09         K:     95         b:   0.03
         r:   0.08

The corresponding US perpetual call prices for the parameter matrix is:

Option 1: 18.5035
Option 2: 18.5035
Option 3: 15.5948
Option 4: 23.7431
Option 5: 21.2616

The corresponding US perpetual put prices for the parameter matrix is:

Option 1: 3.03106
Option 2: 3.03106
Option 3: 2.31494
Option 4: 0.955487
Option 5: 3.38721

C:\Users\jorda\OneDrive - Nexus365\C++\Liu_Jordan Level 9 HW\Group A and B - Exact Pricing Methods\x64\Debug\Groups A and B - Exact Pricing Methods.exe (process 532) exited with code 0.
Press any key to close this window . . .
