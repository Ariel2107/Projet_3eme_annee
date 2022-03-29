import numpy as np
import matplotlib.pyplot as plt

"la on fait plusieurs modifs pour voir ce que ca donne"

X = np.array([[1, 1],
              [2, 3],
              [3, 3]
              ])

Y = np.array([1, -1, -1])

plt.scatter(X[0, 0], X[0, 1], color='blue')
plt.scatter(X[1:3, 0], X[1:3, 1], color='red')
plt.show()
plt.clf()

# Init linear model
W = np.random.uniform(-1, 1.0, 3)

def predict_linear_model_classification(model_weights: np.ndarray, x1: float, x2: float):
    total_sum = 1 * model_weights[0] + x1*model_weights[1] + x2*model_weights[2]
    return 1 if total_sum >= 0 else -1

for inputs in X:
    print(predict_linear_model_classification(W, inputs[0], inputs[1]))

for i in range(0, 1000):
    k = np.random.choice(range(0, len(X)))
    g_x_k = predict_linear_model_classification(W, X[k, 0], X[k, 1])
    y_k = Y[k]
    diff = y_k - g_x_k
    W[0] = W[0] + 0.01 * diff * 1
    W[1:] = W[1:] + 0.01 * diff * X[k]

for inputs in X:
    print(predict_linear_model_classification(W, inputs[0], inputs[1]))

print(W)
plt.scatter(X[0, 0], X[0, 1], color='blue')
plt.scatter(X[1:3, 0], X[1:3, 1], color='red')

predict_x1 = np.arrange(1, 3, 0.01)
predict_x2 = np.arrange(1, 3, 0.01)

"""predicted_class = []
for x1 in predict_x1:
    for x2 in predict_x2:
        predicted_class(1 if predict_linear_model_classification(W, x1, x2) >= 0 else -1)

predicted_class = np.array(predicted_class)
"""
plt.plot([x for x in range(1, 4)], [-W[1]/W[2]*x - W[0]/W[2] for x in range(1, 4)], color='green')
plt.show()
plt.clf()
