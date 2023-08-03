# ConFiLan
- configuration file language
- another file format invented by nikozdev
> the developer who hates a curly brace
> > because that is hard to draw by hand
## configuration file format
- the entire file consists of index-value associations
- tabulations, spaces do not matter
> only strings, squared and rounded braces
- there can be multiple scope levels
> the global scope is the file
> > having the file path as it's own string index
> each scope has it's own set of values
> > nested scopes on higher levels can only reference lower levels
- the lower the level of a scope - the closer to global it is
> the most global file scope has level zero == 0
### index
- this is just a way to access and reference some value
- written in squared brackets like \[this\]
- has to be written before the associated value with following '=' sign
> value=\[index\]
> can also be written before any other index to make an alias
> > \[alias\]=\[index\]=\(value\)
- can be written after the associated value with preceding '=' sign
> value=\[index\]
> can also be written after any other index to make an alias
> > \(value\)=\[index\]=\[alias\]
- this can only be a string
### value
- written in rounded brackets like \(this\)
- associated with an index or multiple aliases
- can be a scope
> then it can contain it's own index-value pairs
> \[index\]=\(\[i\]=\[v\]=\[i\]\)=\[index\]
- this can be just a string
### scope
- value having other values in it
> \[index\]=\(\[index\]=\(value\)=\[alias\]\)=\[alias\]
