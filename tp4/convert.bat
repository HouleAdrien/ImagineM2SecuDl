@echo off

mkdir respng

for %%f in (res\*.ppm) do (
    magick convert "%%f" "respng\%%~nf.png"
)
