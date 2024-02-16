###########################################################
BLACKSCHOLE ( https://gist.github.com/codeslinger/472083/0acc95f745def15a3677b021742b27416a78bcf3 )

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
PASSO A PASSO  -> black_MATH
==================================

riscv32-unknown-elf-gcc black.c -O1 -march=rv32imafdc -o black_math -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_math > out_math.txt

==================================
PASSO A PASSO  -> black_TAYLOR
==================================

riscv32-unknown-elf-gcc black.c -O1 -march=rv32imafdc -o black_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_taylor_EX > out_taylor_EX.txt

diff -Ebwa out_math.txt out_taylor_EX.txt

diff -Ebwa out_taylor_EX.txt out_taylor_t7.txt

**********
riscv32-unknown-elf-gcc black.c -O1 -march=rv32imafdc -o black_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_taylor_t1 > out_taylor_t1.txt

**********
riscv32-unknown-elf-gcc black.c -O1 -march=rv32imafdc -o black_taylor_t7 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_taylor_t7 > out_taylor_t7.txt

**********



==================================
PASSO A PASSO  -> FAST ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"

****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o black_AS_EX.s

riscv32-unknown-elf-gcc black_AS_EX.s -O1 -march=rv32im -o black_AS_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_AS_EX > out_AS_EX.txt

diff -Ebwa out_math.txt out_AS_EX.txt

*******************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o black_AS_t7.s

riscv32-unknown-elf-gcc black_AS_t7.s -O1 -march=rv32im -o black_AS_t7 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_AS_t7 > out_AS_t7.txt

diff -Ebwa out_AS_EX.txt out_AS_t7.txt

==================================
PASSO A PASSO  -> FAST my
==================================
riscv32-unknown-elf-gcc black.c -O1 -march=rv32imafdc -o black_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_FAST_EX > out_fast_EX.txt

diff -Ebwa out_math.txt out_fast_EX.txt

**********
riscv32-unknown-elf-gcc black.c -O1 -march=rv32imafdc -o black_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_FAST_t1 > out_fast_t1.txt

diff -Ebwa out_fast_EX.txt out_fast_t7.txt

**********
riscv32-unknown-elf-gcc black.c -O1 -march=rv32imafdc -o black_FAST_t7 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk black_FAST_t7 > out_fast_t7.txt

**********


==================================
PASSO A PASSO  -> PROF5
==================================
./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_MATH/black_math -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_TAYLOR/black_taylor_t7 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_AS/black_AS_t7 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/black/black_FAST/black_FAST_t7 -m /home/dennard/prof5/models/APPROX_1.json



