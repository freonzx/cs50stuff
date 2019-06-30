# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Pneumonoultramicroscopicsilicovolcanoconiosis is a word invented by the president of the National Puzzlers' League
as a synonym for the disease known as silicosis.It is the longest word in the English language published in
a dictionary, the Oxford English Dictionary, which defines it as "an artificial long word said to mean a lung
disease caused by inhaling very fine ash and sand dust".

## According to its man page, what does `getrusage` do?

getrusage(int who) returns resource usage measures for who. The resource usages are returned in a structure.

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 members:
ru_utime: user CPU time used
ru_stime: system CPU time used
ru_maxrss: maximum resident set size
ru_ixrss: integral shared memory size
ru_idrss: integral unshared data size
ru_isrss: integral unshared stack size
ru_minflt: page reclaims (soft page faults)
ru_majflt: page faults (hard page faults)
ru_nswap: swaps
ru_inblock: block input operations
ru_oublock: block output operations
ru_msgsnd: IPC messages sent
ru_msgrcv: IPC messages received
ru_nsignals: signals received
ru_nvcsw: voluntary context switches
ru_nivcsw: involuntary context switches

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because passing large structs by value is slow and takes up a lot of memory due to copies of those structs
being placed on the stack, that also can lead to stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop starts declaring c to use fgetc on file, which will return a character, the condition of that loop is
that c is different than the end of the file, so it will only go through an iteration if there's a character.
After that the character stored on c will go through an if block to make sure c is an alphanumerical or an
apostrophe and the index is higher than 0, if that's true we append the character in c to the word and increment
the index variable. Another if block is here to make sure that if Index is higher than our Length it will consume
the rest of the string so we don't read more than our buffer string can handle. If the character is a digit it
will be ignored and consumed. Then finally if we hit a space or ponctuation, terminate our word with a null
terminator and increment word counter variable, now we have our word, we pass that to the check function and store
the response on a bool variable. If the word is misspelled (If that bool returned true) we print that word and
increment a counter for misspellings.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

If we used fscanf with the parameter %s we would read the file until a space, tab, or newline character is found,
therefore we could read a string longer than our buffer causing a segmentation fault. There's another issue, since
we'll pass texts as input we will have words with ponctuation and fscanf would read them as if it was part of the
word.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Since those functions don't need to alter the variable, we use const to prevent changes to the string that is being
pointed at.
