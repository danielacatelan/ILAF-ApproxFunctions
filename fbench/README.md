###########################################################
FBENCH (https://www.fourmilab.ch/fbench/)

export PATH=$PATH:/opt/riscv/bin

****************
-> numero de linhas

diff -y  out_math.txt out_AS_t1.txt | wc -l

-> contar ACURÁCIA

diff -Ebwa out_math.txt out_AS_EX.txt

diff -Ebwa out_math.txt out_AS_t1.txt

diff -Ebwa out_math.txt out_AS_t2.txt

diff -Ebwa out_math.txt out_taylor_t1.txt

diff -Ebwa out_math.txt out_taylor_t2.txt

diff -Ebwa out_math.txt out_taylor_EX.txt

diff -Ebwa out_math.txt out_fast_t1.txt

diff -Ebwa out_math.txt out_fast_t2.txt

diff -Ebwa out_math.txt out_fast_EX.txt

###########################################################

riscv32-unknown-elf-gcc susan.c -O1 -march=rv32im -o susan_spike -lm 

time spike --isa=RV32I /opt/riscv/riscv32-unknown-elf/bin/pk susan_spike lena.pgm out.pgm -c -q 

==================================
PASSO A PASSO  -> fbench_MATH
==================================

riscv32-unknown-elf-gcc fbench.c -O1 -march=rv32imafdc -o fbench_math -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_math > out_math.txt

==================================
PASSO A PASSO  -> fbench_TAYLOR
==================================

riscv32-unknown-elf-gcc fbench.c -O1 -march=rv32imafdc -o fbench_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_taylor_EX > out_taylor_EX.txt

diff -Ebwa out_math.txt out_taylor_EX.txt

diff -Ebwa out_taylor_EX.txt out_taylor_t1.txt


**********
riscv32-unknown-elf-gcc fbench.c -O1 -march=rv32imafdc -o fbench_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_taylor_t1 > out_taylor_t1.txt

**********
riscv32-unknown-elf-gcc fbench.c -O1 -march=rv32imafdc -o fbench_taylor_t9 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_taylor_t9 > out_taylor_t9.txt

diff -Ebwa out_taylor_EX.txt out_taylor_t9.txt

**********



==================================
PASSO A PASSO  -> FAST ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"

****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o fbench_AS_EX.s

riscv32-unknown-elf-gcc fbench_AS_EX.s -O1 -march=rv32im -o fbench_AS_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_AS_EX > out_AS_EX.txt

diff -Ebwa out_math.txt out_AS_EX.txt

diff -Ebwa out_AS_EX.txt out_AS_t3.txt

diff -Ebwa out_math.txt out_AS_t2.txt

*******************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o fbench_AS_t9.s

riscv32-unknown-elf-gcc fbench_AS_t9.s -O1 -march=rv32im -o fbench_AS_t9 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_AS_t9 > out_AS_t9.txt

diff -Ebwa out_AS_EX.txt out_AS_t9.txt

==================================
PASSO A PASSO  -> FAST my
==================================
riscv32-unknown-elf-gcc fbench.c -O1 -march=rv32imafdc -o fbench_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_FAST_EX > out_fast_EX.txt

diff -Ebwa out_math.txt out_fast_EX.txt

**********
riscv32-unknown-elf-gcc fbench.c -O1 -march=rv32imafdc -o fbench_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_FAST_t1 > out_fast_t1.txt

**********
riscv32-unknown-elf-gcc fbench.c -O1 -march=rv32imafdc -o fbench_FAST_t9 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fbench_FAST_t9 > out_fast_t9.txt

diff -Ebwa out_fast_EX.txt out_fast_t9.txt

**********


==================================
PASSO A PASSO  -> PROF5
==================================
./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_MATH/fbench_math -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t7 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t8 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_TAYLOR/fbench_taylor_t9 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t7 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t8 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_AS/fbench_AS_t9 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t7 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t8 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/fbench/fbench_FAST/fbench_FAST_t9 -m /home/dennard/prof5/models/APPROX_1.json



