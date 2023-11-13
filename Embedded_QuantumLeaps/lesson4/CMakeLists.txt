# toolchain file:
# .\..\cmake-tutorial\examples\iar-toolchain.cmake

#    ..\hex_and_cut.bat Debug\Exe\projectName.out HexOne.txt "CSTACK$$Limit.__"

cmake_minimum_required(VERSION 3.23)

#instead of in the command line
# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-tutorial/examples/iar-toolchain.cmake)

project(projectName LANGUAGES C)

set(executable_list_ ${CMAKE_PROJECT_NAME})
set(different_files_ main.c)

set(
    low_optimization_compiler_
        --no_cse 
        --no_unroll 
        --no_inline 
        --no_code_motion 
        --no_tbaa 
        --no_clustering 
        --no_scheduling 
        --debug 
        --endian=little 
        --cpu=Cortex-M4 
        -e 
        --fpu=VFPv4_sp 
        --dlib_config "C:\\Program Files\\IAR Systems\\Embedded Workbench 9.1\\arm\\inc\\c\\DLib_Config_Normal.h" 
        -Ol --require_prototypes 
    )
	
set(
    high_optimization_compiler_
        --debug 
        --endian=little 
        --cpu=Cortex-M4 
        -e 
        --fpu=VFPv4_sp 
        --dlib_config "C:\\Program Files\\IAR Systems\\Embedded Workbench 9.1\\arm\\inc\\c\\DLib_Config_Normal.h" 
        -Oh --require_prototypes 
    )

set(index_ 0)
list(LENGTH different_files_ list_length_)

string(LENGTH ${CMAKE_CURRENT_LIST_DIR} temp_length_)
math(EXPR temp_length_ ${temp_length_}+1)
string(SUBSTRING ${CMAKE_CURRENT_BINARY_DIR} ${temp_length_} -1 build_dir_)

# message(STATUS ${CMAKE_CURRENT_BINARY_DIR})
# message(STATUS ${temp_length_})
message(STATUS ${build_dir_})
set(temp_length_ "")


while(${index_} LESS ${list_length_})

	list(GET executable_list_ ${index_} current_exec_ )
    list(GET different_files_ ${index_} current_file_ )

    # ====================================================
    add_executable(${current_exec_})

    target_sources(
        ${current_exec_}
            PRIVATE 
                ${current_file_}
    #            delay.c
    )
    
    target_compile_options(
        ${current_exec_}
            PRIVATE
                ${high_optimization_compiler_} 
    )   
    
    string(REPLACE "/" "\\" CUSTOM_BIN_PATH_ ${CMAKE_CURRENT_BINARY_DIR})
    string(REPLACE "/" "\\" CUSTOM_LIST_PATH_ ${CMAKE_CURRENT_LIST_DIR})
    
    
    target_link_options(
        ${current_exec_}
            PRIVATE
            --no_out_extension 
            #-o  "${CUSTOM_BIN_PATH_}\\projectName.out" 
            # --redirect _Printf=_PrintfFullNoMb 
            # --redirect _Scanf=_ScanfFullNoMb
            --map "${CUSTOM_BIN_PATH_}\\projectName.map"
            --config "${CUSTOM_LIST_PATH_}\\projectName.icf"
            --semihosting 
            --entry __iar_program_start 
            --vfe 
            --text_out locale 
            --cpu=Cortex-M4 
            --fpu=VFPv4_sp 
    )
    
    add_custom_command(TARGET ${current_exec_}
        POST_BUILD COMMAND "C:\\Program Files\\IAR Systems\\Embedded Workbench 9.1\\arm\\bin\\ielfdumparm.exe"  --code --source projectName.elf -o ${current_exec_}.s
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
    )

    # dumps the contents of the xecutables into .txt and removes the lines after first occurence of given strings from these text files
    # add_custom_command(TARGET ${current_exec_}
    #     POST_BUILD COMMAND ..\\hex_and_cut.bat ${build_dir_}\\${current_exec_}.elf ${current_exec_}_hex.txt "C:"
    #     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/
    # )

    # ====================================================

	math(EXPR index_ "${index_} + 1")
endwhile()

