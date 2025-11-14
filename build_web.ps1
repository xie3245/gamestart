param(
  [string]$EmsdkRoot = "E:\Dev\emsdk",   # <-- change if your emsdk lives elsewhere
  [string]$Config    = "MinSizeRel",        # Debug/Release (used for Multi-Config)
  [int]   $Port      = 8080,             # emrun port
  [string]$Target    = "Slurpwave"       # your target/basename (produces Slurpwave.html)
)

$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $here

# 0) Load Emscripten env (bypass policy only for this PS session)
$envPs1 = Join-Path $EmsdkRoot "emsdk_env.ps1"
if (-not (Test-Path $envPs1)) {
  throw "emsdk_env.ps1 not found at '$envPs1'. Set -EmsdkRoot to your emsdk folder."
}
# Allow this session to run the env script
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass -Force
& $envPs1

# Verify tools
if (-not (Get-Command emcmake -ErrorAction SilentlyContinue)) { throw "emcmake not found (emsdk env not loaded?)" }
if (-not (Get-Command emrun   -ErrorAction SilentlyContinue)) { throw "emrun not found (emsdk env not loaded?)" }

# 1) Pick generator
#$haveNinja = (Get-Command ninja -ErrorAction SilentlyContinue) -ne $null
#$gen = $haveNinja ? "Ninja Multi-Config" : "MinGW Makefiles"
#$multi = $gen -like "*Multi-Config"
#Write-Host "Using generator: $gen"

# 2) Configure
$buildDir = Join-Path $here "build_web"
$cmakeArgs = @(
  "-S", ".", "-B", $buildDir, "-DCMAKE_BUILD_TYPE=$Config"
)


Write-Host "`n=== Configure ==="
emcmake cmake @cmakeArgs

# 3) Build
Write-Host "`n=== Build ($Config) ==="
cmake --build $buildDir -j


# 4) Locate output (.html/.wasm/.data)
$outDir = Join-Path $buildDir $Config
$html   = Join-Path $outDir "$Target.html"
if (-not (Test-Path $html)) {
  # Fallback: grab the first html in the folder
  $firstHtml = Get-ChildItem $outDir -Filter *.html | Select-Object -First 1
  if ($firstHtml) { $html = $firstHtml.FullName }
}

if (-not (Test-Path $html)) { throw "No .html found in '$outDir'. Did your target name change?" }

# Optional: sanity check the .data
$data = [System.IO.Path]::ChangeExtension($html, ".data")
if (-not (Test-Path $data)) {
  Write-Warning "'.data' file not found next to '$([IO.Path]::GetFileName($html))'. If your game needs assets, check your --preload-file CMake flags."
}

# 5) Run with emrun (serves & opens browser)
Write-Host "`n=== Run ==="
Write-Host "Serving '$([IO.Path]::GetFileName($html))' on http://localhost:$Port/"
emrun --port $Port $html
