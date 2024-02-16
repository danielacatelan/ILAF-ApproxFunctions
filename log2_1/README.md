###########################################################
log2 (  )

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

==================================
PASSO A PASSO  -> log2_MATH
==================================

riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_math -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_math > out_math.txt

==================================
PASSO A PASSO  -> log2_TAYLOR
==================================

riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_taylor_EX > out_taylor_EX.txt

diff -Ebwa out_math.txt out_taylor_EX.txt

diff -Ebwa out_taylor_EX.txt out_taylor_t1.txt

**********
riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_taylor_t1 > out_taylor_t1.txt

**********
riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_taylor_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_taylor_t2

 > out_taylor_t7.txt

**********
riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_taylor_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_taylor_t3

 > out_taylor_t7.txt


==================================
PASSO A PASSO  -> ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"

****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o log2_1_AS_EX.s

riscv32-unknown-elf-gcc log2_1_AS_EX.s -O1 -march=rv32im -o log2_1_AS_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_1_AS_EX > out_1_AS_EX.txt

diff -Ebwa out_log2_1_math.txt out_1_AS_EX.txt

*******************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o log2_1_AS_t2.s

riscv32-unknown-elf-gcc log2_1_AS_t2.s -O1 -march=rv32im -o log2_1_AS_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_1_AS_t2 > out_1_AS_t2.txt

diff -Ebwa out_1_AS_EX.txt out_1_AS_t2.txt

==================================
PASSO A PASSO  -> FAST my
==================================
riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_1_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_1_FAST_EX > out_1_fast_EX.txt

diff -Ebwa out_log2_1_math.txt out_1_fast_EX.txt

**********
riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_1_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_1_FAST_t1 > out_1_fast_t1.txt

diff -Ebwa out_1_fast_EX.txt out_1_fast_t2.txt

**********
riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_1_FAST_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_1_FAST_t2 > out_1_fast_t2.txt

**********
riscv32-unknown-elf-gcc log2.c -O1 -march=rv32imafdc -o log2_FAST_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk log2_FAST_t3 

==================================
PASSO A PASSO  -> PROF5
==================================
./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/log2_1/log2_MATH/log2_1_math -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/log2_1/log2_AS/log2_1_AS_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/log2_1/log2_AS/log2_1_AS_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/log2_1/log2_AS/log2_1_AS_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/log2_1/log2_FAST/log2_1_FAST_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/log2_1/log2_FAST/log2_1_FAST_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/log2_1/log2_FAST/log2_1_FAST_t2 -m /home/dennard/prof5/models/APPROX_1.json


