# `lndl` Syntax
## Example
```ruby
LANGUAGE(language_name) # < internal name
#: A comment starting with <hash><colon> will be parsed as the description.

	DisplayName: Language name # may contain special characters and spaces

	# The above example will be shown to the user as: (example formating)
	# +----------------+
	# | Language namee |	<language_name>
	# +================+------------------------+
	# | A comment starting with #<hash>:<colon> |
	# | will be parsed as the description.      |
	# +-----------------------------------------+


	REGISTER_STORAGE(0x00)
	#: A register storage is a definition of all the processor's registers, mapped as if they are static variables within a separate memory space.
		Size:	8 BYTES

		# Registers:
		#  - Can be thought of as:
		#	 struct
		#	 {
		#		unsigned char F;
		#		unsigned char A;
		#	 } AF;
		REGISTER(AF)
		{
			Mapping:	0x00	# This register will cover space 0x00 - 0x0f
			Size:		16 BITS	# Valid modifiers are BITS and BYTES. Defaults to BITS if left out.
			Purpose: 	GENERAL	# Attach any functionality to this register
		},

		REGISTER(F)
		{
			Mapping:	0x00
			Size:		8 BITS
			Purpose:	FLAGS	# This register is a bitfield holding our flags defined below
		},
		REGISTER(A)
		{
			Mapping:	0x08
			Size:		8 BITS
			Purpose:	GENERAL
		}
	END_REGISTER_STORAGE


```