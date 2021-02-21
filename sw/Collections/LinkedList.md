# Linked List Implementation

## Keeping this Implmentation Generic for Reuse

In an attempt to make this linked list structure generic, the data inside of the Node structure is simply a void pointer. 

## Type Protection

Currently the mechanism for type protection is very loose. The linked list has an integer member
that the user can use to assign a type to the data of the linked list.
Each linked list function then requires an integer argument representing this type to be passed in to allow the execution of the function.
The decision of which integer represents which data type will be left to the user of the linked list and should be consistent through multiple uses of the linked list in their application.

## Freeing The Linked List

Since the Node has a void* for its data member, we do not know ahead of time how to free that data member.
Therefore, the user must provide a function pointer as an argument to the free_linked_list() function defining how to free its data type.