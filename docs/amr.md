# Adaptive Mesh Refinement

There are two ways to control AMR in parthenon.  First, built-in refinemnt criteria can be activated at runtime via the input file.  Second, package developers can create a package-specific refinement tagging function to allow for more tailored criteria of less generic applicability.

## Enable AMR
To enable AMR, the following lines are required in the `<mesh>` block of your input file.
```c++
refinement = adaptive    # enable adaptive mesh refinement
numlevel = 5             # how many refined levels can parthenon produce
```

## Built-in 
Parthenon includes the ability to tag cells for refinement/derefinement based on predefined criteria that can be enabled at runtime in the input file.  Multiple criteria can be enabled simultaneously, in which case the most refined criteria wins.  If ``refinement=adaptive`` has been specified as above, parthenon will initialize your AMR choices by looking for blocks with names ``<Refinement#>`` where ``#`` is a zero-based sequential indexing of Refinement criteria.  An input file might looks like
```c++
<mesh>
refinement = adaptive
...

<Refinement0>
...

<Refinement1>
...

<Refinement2>
...
```
In each refinement block, you are required to provide a ``method`` which is a string that selects among the provided critera (listed below).  Additionally, you are required to provide a ``field`` which must be a valid variable name in the application.  Optionally, you can provide a ``refine_tol`` value (defaults to 0.5) indicating that a block should be tagged for refinement if the criteria selected evaluates to a value above this threshold anywhere on the block.  Similarly, the ``derefine_tol`` value (default 0.05) determines when derefinement can occur (all values of the criteria function must be less than this).  Finally, an integer ``max_level`` value can be specified that limits refinement triggered by this criteria to no greater than this level.  The default is to allow each criteria to refine to ``numlevel``, which is the global maximum number of refinement levels specified in the ``<mesh>`` block.

### Predefined Criteria
| Method | Description |
|--------|-------------|
| derivative_order_1 | ![formula](https://render.githubusercontent.com/render/math?math=\|dlnq\/dlnx\|), where q is the user selected variable |

## Package-specific Criteria
As a package developer, you can define a tagging function that takes a ``Container`` as an argument and returns an integer in {-1,0,1} to indicate the block should be derefined, left alone, or refined, respectively.  This function should be registered in a ``StateDescriptor`` object by assigning the ``CheckRefinement`` function pointer to point at the packages function.  An example is demonstrated [here](../example/calculate_pi/pi.cpp).
