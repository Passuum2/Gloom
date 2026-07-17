Write-Host "Compiling Gloom project..."
gcc -g -O2 -I include src/*.c -L lib/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -o bin/Gloom.exe

if ($LASTEXITCODE -eq 0) {
    Write-Host "Running Gloom project..." -ForegroundColor Blue
    .\bin\Gloom.exe
} else {
    Write-Host "Build failed!" -ForegroundColor Red
}
