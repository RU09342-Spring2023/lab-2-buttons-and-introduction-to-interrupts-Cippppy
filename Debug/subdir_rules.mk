################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
GPIO_Driver.obj: C:/Users/Cip/Documents/School/Semester\ 4/Embedded/lab-1-gpio-demo-and-driver-Cippppy/4\ GPIO\ Driver/GPIO_Driver.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="C:/ti/ccs1220/ccs/ccs_base/msp430/include" --include_path="C:/Users/Cip/Documents/School/Semester 4/Embedded/lab-2-buttons-and-introduction-to-interrupts-Cippppy" --include_path="C:/Users/Cip/Documents/School/Semester 4/Embedded/lab-1-gpio-demo-and-driver-Cippppy/4 GPIO Driver" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR2355__ --define=_FRWP_ENABLE --define=_INFO_FRWP_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="GPIO_Driver.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

4\ Designing\ an\ Intruder\ Security\ System/OccupancyDetector.obj: C:/Users/Cip/Documents/School/Semester\ 4/Embedded/lab-2-buttons-and-introduction-to-interrupts-Cippppy/4\ Designing\ an\ Intruder\ Security\ System/OccupancyDetector.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="C:/ti/ccs1220/ccs/ccs_base/msp430/include" --include_path="C:/Users/Cip/Documents/School/Semester 4/Embedded/lab-2-buttons-and-introduction-to-interrupts-Cippppy" --include_path="C:/Users/Cip/Documents/School/Semester 4/Embedded/lab-1-gpio-demo-and-driver-Cippppy/4 GPIO Driver" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR2355__ --define=_FRWP_ENABLE --define=_INFO_FRWP_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="OccupancyDetector.d_raw" --obj_directory="4 Designing an Intruder Security System" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


