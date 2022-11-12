rmdir /S /Q ".vs"
rmdir /S /Q "fastman92 limit adjuster\Intermediate"
rmdir /S /Q "fastman92 limit adjuster external loader\Intermediate"
rmdir /S /Q "fastman92 plugin loader\Intermediate"
del /f "fastman92 projects.db3"
IF /I "%1" NEQ "/no_pause" pause