###########################################################
BISSECÇÃO (  )

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
PASSO A PASSO  -> bis_MATH
==================================

riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_math -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_math > out_math.txt

==================================
PASSO A PASSO  -> bis_TAYLOR
==================================

riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_taylor_EX > out_taylor_EX.txt

diff -Ebwa out_math.txt out_taylor_EX.txt

diff -Ebwa out_taylor_EX.txt out_taylor_t7.txt

**********
riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_taylor_t1 > out_taylor_t1.txt

**********
riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_taylor_t7 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_taylor_t7 > out_taylor_t7.txt

**********



==================================
PASSO A PASSO  -> ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"

****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o bis_AS_EX.s

riscv32-unknown-elf-gcc bis_AS_EX.s -O1 -march=rv32im -o bis_AS_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_AS_EX > out_AS_EX.txt

diff -Ebwa out_math.txt out_AS_EX.txt

*******************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o bis_AS_t3.s

riscv32-unknown-elf-gcc bis_AS_t3.s -O1 -march=rv32im -o bis_AS_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_AS_t3 

> out_AS_t7.txt

diff -Ebwa out_AS_EX.txt out_AS_t7.txt

==================================
PASSO A PASSO  -> FAST my
==================================
riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_FAST_EX 

> out_fast_EX.txt

diff -Ebwa out_math.txt out_fast_EX.txt

**********
riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_FAST_t1 

> out_fast_t1.txt

diff -Ebwa out_fast_EX.txt out_fast_t7.txt

**********
riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_FAST_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_FAST_t2 

> out_fast_t7.txt

**********
riscv32-unknown-elf-gcc bisseccao.c -O1 -march=rv32imafdc -o bis_FAST_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk bis_FAST_t3 

==================================
PASSO A PASSO  -> PROF5
==================================
./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_MATH/bis_math -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_TAYLOR/bis_taylor_t7 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_AS/bis_AS_t7 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_t4 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_t5 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_t6 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/bis/bis_FAST/bis_FAST_t7 -m /home/dennard/prof5/models/APPROX_1.json



