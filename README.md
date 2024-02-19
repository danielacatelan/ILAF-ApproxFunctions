Instruction-Level Approximate Function (ILAF)

This work present the Instruction-Level Approximate Function (ILAF), 
an approach that incorporates integer and FP approximate instructions 
into mathematical functions such as sine, cosine, tangent, exponential, 
and logarithmic. The technique was built on top of the  ACCEPT framework. 

In the experimental setup, we have adopted the SPIKE and Prof5 tools. 
ACCEPT was employed to replace the initial user-driven functions to the 
ILAF approach. After that, the application code was translated to RISC-V 
instructions. SPIKE was extended to accommodate new approximate instructions 
following the RISC-V format, and the updated version is called SPIKEX.


The work carried out experiments looking at the accuracy (RE), number 
of instructions, number of cycles, and power($\mu$W). The proposed 
technique (ILAF), the technique used by ACCEPT (AS), and the original 
baseline code (BL) were evaluated in a set of $6$ applications. 
ILAF has proven effective in improving performance (less cycles) while 
maintaining the same level of accuracy of AS and BL in most applications. 
Specifically,  the FBENCH and IDENTITY\_LOG2 applications showed an average 
reduction of $6.78\%$ and $2.84\%$, respectively, compared to BL. Additionally, 
the BLACKSCHOLE application had a reduction of $1.67\%$ in power consumption, 
while the FFBENCH application achieved a $0.03\%$ improvement in the number of cycles. 
Finally, the CUBIC application did not achieved performance improvements 
(had an average reduction of $0.41\%$) compared to the AS technique.

We also evaluated the ILAF technique applied in the Taylor Series, 
with promising results that can be expanded. 
