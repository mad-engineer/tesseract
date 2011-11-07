function qtinfo()
	command=sprintf("qtoctave-info-reader %s > /dev/null", info_file);
	printf("Starting info: %s\n", command);
	system(command, 1, "async");
endfunction
