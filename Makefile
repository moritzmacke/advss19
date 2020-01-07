##
## Example Makefile for AdvSecSysEng Lab1
##
# The submission archive will be extracted in /home/unprivileged and make will
# be invoked with these targets as user 'unprivileged' from this directory.
##
# Targets for vulnerable programs in the category A 'Stack Based Buffer Overflow'
#
# You need to implement at most one target per category
#
# Each implemented target must remove the 'NOT IMPLEMENTED' output, and produce
# an executable that has the same name as the target identifier.

vuln_stackoverflow-entry: vuln_stackoverflow-entry.c
	gcc_options="-m32 -fno-stack-protector -D_FORTIFY_SOURCE=0 -z execstack -z norelro -no-pie" ; \
	gcc $$gcc_options -o $@ $<

vuln_stackoverflow-medium: 
	gcc_options="-fno-stack-protector -D_FORTIFY_SOURCE=0 -z relro -no-pie"
	@echo 'NOT IMPLEMENTED'

vuln_stackoverflow-advanced:
	gcc_options="-fstack-protector-all -D_FORTIFY_SOURCE=0 -z relro -z now -fpie -pie "
	@echo 'NOT IMPLEMENTED'

vuln_stackoverflow-elite:
	clang_options="-fstack-protector-all -D_FORTIFY_SOURCE=2 -z relro -z now -fpie -pie -flto -fsanitize=cfi -fsanitize=safe-stack -fuse-ld=gold"
	@echo 'NOT IMPLEMENTED'


# Targets for vulnerable programs in the category B 'Format-String Vulnerabilities'
#
# You need to implement at most one target per category
#
# Each implemented target must remove the 'NOT IMPLEMENTED' output, and produce
# an executable that has the same name as the target identifier.

vuln_formatstring-entry: vuln_formatstring-entry.c
	gcc_options="-fno-stack-protector -D_FORTIFY_SOURCE=0 -z execstack -z norelro -no-pie -g -m32" ; \
	gcc $$gcc_options -o $@ $<

vuln_formatstring-medium:
	gcc_options="-fno-stack-protector -D_FORTIFY_SOURCE=0 -z relro -no-pie"
	@echo 'NOT IMPLEMENTED'

vuln_formatstring-advanced:
	gcc_options="-fstack-protector-all -D_FORTIFY_SOURCE=0 -z relro -z now -fpie -pie "
	@echo 'NOT IMPLEMENTED'

vuln_formatstring-elite:
	clang_options="-fstack-protector-all -D_FORTIFY_SOURCE=2 -z relro -z now -fpie -pie -flto -fsanitize=cfi -fsanitize=safe-stack -fuse-ld=gold"
	@echo 'NOT IMPLEMENTED'



# Targets for vulnerable programs in the category C 'Heap Corruption'
#
# You need to implement at most one target per category
#
# Each implemented target must remove the 'NOT IMPLEMENTED' output, and produce
# an executable that has the same name as the target identifier.

vuln_heapcorruption-entry: 
	gcc_options="-fno-stack-protector -D_FORTIFY_SOURCE=0 -z execstack -z norelro -no-pie" 
	@echo 'NOT IMPLEMENTED'

vuln_heapcorruption-medium: vuln_heapcorruption-medium.c 
	gcc_options="-fstack-protector-all -D_FORTIFY_SOURCE=0 -z relro -no-pie" ; \
	gcc $$gcc_options -o $@ $<

vuln_heapcorruption-advanced:
	gcc_options="-fstack-protector-all -D_FORTIFY_SOURCE=0 -z relro -z now -fpie -pie "
	@echo 'NOT IMPLEMENTED'

vuln_heapcorruption-elite:
	clang_options="-fstack-protector-all -D_FORTIFY_SOURCE=2 -z relro -z now -fpie -pie -flto -fsanitize=cfi -fsanitize=safe-stack -fuse-ld=gold"
	@echo 'NOT IMPLEMENTED'


# The grading robot will set the permissions of the vulnerable programs using the 'install' target.

vuln_programs =  vuln_stackoverflow-entry vuln_stackoverflow-medium vuln_stackoverflow-advanced vuln_stackoverflow-elite
vuln_programs += vuln_formatstring-entry vuln_formatstring-medium vuln_formatstring-advanced vuln_formatstring-elite
vuln_programs += vuln_heapcorruption-entry vuln_heapcorruption-medium vuln_heapcorruption-advanced vuln_heapcorruption-elite

install: $(vuln_programs)
	$(foreach vuln_program, $(vuln_programs), [ -e $(vuln_program) ] && ( sudo chown privileged $(vuln_program) ) || true ;)
	$(foreach vuln_program, $(vuln_programs), [ -e $(vuln_program) ] && ( sudo chmod u+s $(vuln_program) ) || true ;)
	

# Implement, similarly, your chosen exploit targets
#

#exploit_stackoverflow-entry: vuln_stackoverflow-entry
#	@echo 'NOT IMPLEMENTED'
exploit_stackoverflow-entry: exploit_stackoverflow-entry.py vuln_stackoverflow-entry
	/bin/bash -c 'source /home/vagrant/python-virtualenv/pwn/bin/activate; \
	python ./exploit_stackoverflow-entry.py'


exploit_stackoverflow-medium: vuln_stackoverflow-medium
	@echo 'NOT IMPLEMENTED'

exploit_stackoverflow-advanced: vuln_stackoverflow-advanced
	@echo 'NOT IMPLEMENTED'

exploit_stackoverflow-elite: vuln_stackoverflow-elite
	@echo 'NOT IMPLEMENTED'

exploit_formatstring-entry: exploit_formatstring-entry.py vuln_formatstring-entry
	/bin/bash -c 'source /home/vagrant/python-virtualenv/pwn/bin/activate; \
	python ./exploit_formatstring-entry.py'

exploit_formatstring-medium: vuln_formatstring-medium
	@echo 'NOT IMPLEMENTED'

exploit_formatstring-advanced: vuln_formatstring-advanced
	@echo 'NOT IMPLEMENTED'

exploit_formatstring-elite: vuln_formatstring-elite
	@echo 'NOT IMPLEMENTED'

exploit_heapcorruption-entry: exploit.py vuln_heapcorruption-entry
	@echo 'NOT IMPLEMENTED'

exploit_heapcorruption-medium: vuln_heapcorruption-medium
	/bin/bash -c 'python ./exploit_heapcorruption-medium.py | ./vuln_heapcorruption-medium'

exploit_heapcorruption-advanced: vuln_heapcorruption-advanced
	@echo 'NOT IMPLEMENTED'

exploit_heapcorruption-elite: vuln_heapcorruption-elite
	@echo 'NOT IMPLEMENTED'

