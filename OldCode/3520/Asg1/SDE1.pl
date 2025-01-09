% Flower definitions
flower(daisies, med, wet, yellow).
flower(roses, med, dry, red).
flower(petunias, med, wet, pink).
flower(daffodils, med, wet, yellow).
flower(begonias, tall, wet, white).
flower(snapdragons, tall, dry, red).
flower(marigolds, short, wet, yellow).
flower(gardenias, med, wet, red).
flower(gladiolas, tall, wet, red).
flower(bird_of_paradise, tall, wet, white).
flower(lilies, short, dry, white).
flower(azalea, med, dry, pink).
flower(buttercup, short, dry, yellow).
flower(poppy, med, dry, red).
flower(crocus, med, dry, orange).
flower(carnation, med, wet, white).
flower(tulip, short, wet, red).
flower(orchid, short, wet, white).
flower(chrysanthemum, tall, dry, pink).
flower(dahlia, med, wet, purple).
flower(geranium, short, dry, red).
flower(lavender, short, dry, purple).
flower(iris, tall, dry, purple).
flower(peonies, short, dry, pink).
flower(periwinkle, med, wet, purple).
flower(sunflower, tall, dry, yellow).
flower(violet, short, dry, purple).
flower(zinnia, short, wet, yellow).

% Size definitions for easier comparison
size(small, 1).
size(med, 2).
size(tall, 3).

% Helper predicate to compare sizes within an allowed difference
size_adjacent(Size1, Size2) :-
    size(Size1, Value1),
    size(Size2, Value2),
    Diff is abs(Value1 - Value2),
    Diff =< 1.

% Plant assignment 
plantassign(0, []).
plantassign(N, [Flower|Rest]) :-
    N > 0,
    N1 is N - 1,
    plantassign(N1, Rest),
    flower(Flower, _, _, _),
    \+ member(Flower, Rest).

% Unique check to ensure no duplicate flowers
uniquecheck(List) :- uniquecheck_helper(List, []).

uniquecheck_helper([], _).
uniquecheck_helper([Flower|Rest], Seen) :-
    \+ member(Flower, Seen),
    uniquecheck_helper(Rest, [Flower|Seen]).

% Color check to ensure no adjacent flowers have the same color
colorcheck([_]).
colorcheck([Flower1, Flower2|Rest]) :-
    flower(Flower1, _, _, Color1),
    flower(Flower2, _, _, Color2),
    Color1 \= Color2,
    colorcheck([Flower2|Rest]).

% Size check to ensure adjacent flowers do not have a size difference greater than one step
sizecheck([_]).
sizecheck([Flower1, Flower2|Rest]) :-
    flower(Flower1, Size1, _, _),
    flower(Flower2, Size2, _, _),
    size_adjacent(Size1, Size2),
    sizecheck([Flower2|Rest]).

% Wet/Dry check to validate outermost and innermost plantings
wetcheck(N, List) :-
    nth1(1, List, First),
    nth1(N, List, Last),
    flower(First, _, dry, _),
    flower(Last, _, dry, _),
    MiddleIndex is N // 2,
    Middle1Index is MiddleIndex, % No need for calculation, just added for clarity
    Middle2Index is MiddleIndex + 1,
    nth1(Middle1Index, List, Middle1),
    nth1(Middle2Index, List, Middle2),
    flower(Middle1, _, wet, _),
    flower(Middle2, _, wet, _).

% Writing the garden layout
writegarden([]).
writegarden([H|T]) :-
    write(H), nl,
    writegarden(T).

% Main predicate to generate and validate a garden plan
gardenplan(N, List) :-
    % Check if N is even
    (   N mod 2 =:= 0
    ->  true % Proceed if N is even
    ;   write('Error: N must be an even number.'), nl, fail % Inform the user and fail if N is not even
    ),
    plantassign(N, List),
    uniquecheck(List),
    colorcheck(List),
    sizecheck(List),
    wetcheck(N, List),
    writegarden(List).









needs improvement, delete this if you don't care or want to fix it