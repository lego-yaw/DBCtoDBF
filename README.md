# DBCtoDBF_jll.jl
+ This is a julia binary wrapper for converting .dbc files to .dbf files
+ This converter was specifically adpated to converting .dbc files of DATASUS(Brasil public Healthcare information system) 

# How to use
```
>>> using Pkg
>>> Pkg.add("DBCtoDBF_jll")
>>> using DBCtoDBF_jll
>>> exe_path = dcb2dbf()
>>> run(`$exe_path $input_file $output_file`) # input_file = file.dbc  # output_file = file.dbF
```

# NOTE
+ Wrapper has been added to function created here https://github.com/lego-yaw/ReadDBC.jl

# Citation
+ This project is based on the work of https://github.com/madler/zlib/tree/master/contrib/blast and https:// github.com/eaglebh/blast-dbf and the R version developed by danicat(https://github.com/danicat/read.dbc). Also this package wouldn't have been possible without DBFTable (https://github.com/JuliaData/DBFTables.jl)

# Help
+ if you have any questions or suggestions, feel free to contact at amenubright2@gmail.com

# Created source code
## lego-yaw/DBCtoDBF_jll.jl
