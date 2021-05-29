./ltnc example/asmEmbed/asmEmbed.asm.ltn example/asmEmbed/asmEmbed.ltn
./ltna example/asmEmbed/asmEmbed.hex.ltn example/asmEmbed/asmEmbed.asm.ltn -hex
./ltnvm -run example/asmEmbed/asmEmbed.hex.ltn -hex
rm example/asmEmbed/asmEmbed.asm.ltn
rm example/asmEmbed/asmEmbed.hex.ltn