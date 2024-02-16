###########################################################
CUBIC (MiBENCH)
###########################################################

riscv32-unknown-elf-gcc susan.c -O1 -march=rv32im -o susan_spike -lm 

time spike --isa=RV32I /opt/riscv/riscv32-unknown-elf/bin/pk susan_spike lena.pgm out.pgm -c -q 

==================================
PASSO A PASSO  -> CUBIC_MATH
==================================

riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_math -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_math

==================================
PASSO A PASSO  -> CUBIC_TAYLOR
==================================

riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_taylor_EX

**********
riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_taylor_t1

**********
riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_taylor_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_taylor_t2

**********
riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_taylor_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_taylor_t3


==================================
PASSO A PASSO  -> FAST ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"

make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o cubic_AS_t3.s

riscv32-unknown-elf-gcc cubic_AS_t3.s -O1 -march=rv32im -o cubic_AS_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_AS_t3

==================================
PASSO A PASSO  -> FAST my
==================================
riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_FAST_EX

**********
riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_FAST_t1

**********
riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_FAST_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_FAST_t2

**********
riscv32-unknown-elf-gcc cubic.c -O1 -march=rv32imafdc -o cubic_FAST_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk cubic_FAST_t3

==================================
PASSO A PASSO  -> PROF5
==================================
./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_MATH/cubic_math -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_TAYLOR/cubic_taylor_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_TAYLOR/cubic_taylor_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_TAYLOR/cubic_taylor_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_TAYLOR/cubic_taylor_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_AS/cubic_AS_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_AS/cubic_AS_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_AS/cubic_AS_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_AS/cubic_AS_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_FAST/cubic_FAST_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_FAST/cubic_FAST_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_FAST/cubic_FAST_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/cubic/CUBIC_FAST/cubic_FAST_t3 -m /home/dennard/prof5/models/APPROX_1.json


