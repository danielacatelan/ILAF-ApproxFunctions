###########################################################
FFT ( )

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
PASSO A PASSO  -> fft_MATH
==================================

riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_math -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_math > out_math.txt

==================================
PASSO A PASSO  -> fft_TAYLOR
==================================

riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_taylor_EX > out_taylor_EX.txt

diff -Ebwa out_math.txt out_taylor_EX.txt

diff -Ebwa out_math.txt out_taylor_t2.txt

diff -Ebwa out_taylor_EX.txt out_taylor_t2.txt

**********
riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_taylor_t1 > out_taylor_t1.txt

**********
riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_taylor_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_taylor_t2 > out_taylor_t2.txt

**********



==================================
PASSO A PASSO  -> FAST ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"

****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o fft_AS_EX.s

riscv32-unknown-elf-gcc fft_AS_EX.s -O1 -march=rv32im -o fft_AS_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_AS_EX > out_AS_EX.txt

diff -Ebwa out_math.txt out_AS_EX.txt

*******************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o fft_AS_t3.s

riscv32-unknown-elf-gcc fft_AS_t3.s -O1 -march=rv32im -o fft_AS_t3 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_AS_t3 > out_AS_t3.txt

diff -Ebwa out_math.txt out_AS_t3.txt

==================================
PASSO A PASSO  -> FAST my
==================================
riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_FAST_EX > out_fast_EX.txt

diff -Ebwa out_math.txt out_fast_EX.txt

diff -Ebwa out_math.txt out_fast_t2.txt

diff -Ebwa out_fast_EX.txt out_fast_t2.txt

**********
riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_FAST_t1 > out_fast_t1.txt

**********
riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_FAST_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_FAST_t2 > out_fast_t2.txt

**********
riscv32-unknown-elf-gcc fft.c -O1 -march=rv32imafdc -o fft_FAST_t3_i -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk fft_FAST_t3_i > out_fast_t3_i.txt

**********


==================================
PASSO A PASSO  -> PROF5
==================================
./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_MATH/fft_math -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_TAYLOR/fft_taylor_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_TAYLOR/fft_taylor_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_TAYLOR/fft_taylor_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_AS/fft_AS_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_AS/fft_AS_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_AS/fft_AS_t2 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_AS/fft_AS_t3 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_FAST/fft_FAST_EX -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_FAST/fft_FAST_t1 -m /home/dennard/prof5/models/APPROX_1.json

./prof5 -i RV32IMAFDC /home/dennard/accept/Func_Approx/FFT/FFT_FAST/fft_FAST_t2 -m /home/dennard/prof5/models/APPROX_1.json



