###########################################################
FFBENCH (https://www.fourmilab.ch/fbench/)

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
PASSO A PASSO  -> ffbench_MATH
==================================

riscv32-unknown-elf-gcc ffbench.c -O1 -march=rv32imafdc -o ffbench_math -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_math > out_math.txt

==================================
PASSO A PASSO  -> ffbench_TAYLOR
==================================

riscv32-unknown-elf-gcc ffbench.c -O1 -march=rv32imafdc -o ffbench_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_taylor_EX > out_taylor_EX.txt

**********
riscv32-unknown-elf-gcc ffbench.c -O1 -march=rv32imafdc -o ffbench_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_taylor_t1 > out_taylor_t1.txt

**********
riscv32-unknown-elf-gcc ffbench.c -O1 -march=rv32imafdc -o ffbench_taylor_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_taylor_t2 > out_taylor_t2.txt

**********



==================================
PASSO A PASSO  -> FAST ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"
****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o ffbench_AS_EX.s

riscv32-unknown-elf-gcc ffbench_AS_EX.s -O1 -march=rv32im -o ffbench_AS_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_AS_EX > out_AS_EX.txt
*******************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o ffbench_AS_t2.s

riscv32-unknown-elf-gcc ffbench_AS_t2.s -O1 -march=rv32im -o ffbench_AS_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_AS_t2 > out_AS_t2.txt

==================================
PASSO A PASSO  -> FAST my
==================================
riscv32-unknown-elf-gcc ffbench.c -O1 -march=rv32imafdc -o ffbench_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_FAST_EX > out_fast_EX.txt

**********
riscv32-unknown-elf-gcc ffbench.c -O1 -march=rv32imafdc -o ffbench_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_FAST_t1 > out_fast_t1.txt

**********
riscv32-unknown-elf-gcc ffbench.c -O1 -march=rv32imafdc -o ffbench_FAST_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ffbench_FAST_t2 > out_fast_t2.txt

**********


==================================
PASSO A PASSO  -> PROF5
==================================
./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_MATH/ffbench_math -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_TAYLOR/ffbench_taylor_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_TAYLOR/ffbench_taylor_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_TAYLOR/ffbench_taylor_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_AS/ffbench_AS_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_AS/ffbench_AS_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_AS/ffbench_AS_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_FAST/ffbench_FAST_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_FAST/ffbench_FAST_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/ffbench/ffbench_FAST/ffbench_FAST_t2 -m /home/dennard/prof5/models/APPROX_1.json



