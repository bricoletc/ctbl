import pandas as pd
def integer_set(fi):
    with open(fi) as f:
        answer=f.readlines()

    lambdaf=lambda x:int(x.strip(),2)

    answer=set(map(lambdaf,answer))

    return answer

answer_file="answer.txt"
solution_file="simulated_solution.txt"

answer=integer_set(answer_file)
solution=integer_set(solution_file)

print("Length answer: {} \t Length solution: {}".format(len(answer),len(solution)))
print(answer.difference(solution)) #If empty set, then the answers are identical
