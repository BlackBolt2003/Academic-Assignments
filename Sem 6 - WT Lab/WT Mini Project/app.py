from flask import Flask, render_template, jsonify, request
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from sklearn.preprocessing import StandardScaler
import pandas as pd
import random

app = Flask(__name__)

# Sample DataFrame (replace with your dataset)
filePath = "Cleaned_Indian_Food_Dataset.csv"
df = pd.read_csv(filePath)
meal_plan = []

# Recipe recommendation system ------------------------------------------------

def recommend_recipe(ingredients):
    # Feature extraction using TF-IDF
    tfidf_vectorizer = TfidfVectorizer()
    ingredient_matrix = tfidf_vectorizer.fit_transform(df['Cleaned-Ingredients'])

    # User input
    user_input_list = ingredients.split(', ')

    user_vector = tfidf_vectorizer.transform([' '.join(user_input_list)])

    # Calculate cosine similarity
    cosine_sim = cosine_similarity(user_vector, ingredient_matrix).flatten()

    # Rank recipes based on similarity
    df['similarity'] = cosine_sim

    # Filter and display only relevant recipes (non-zero similarity)
    relevant_recipes = df[df['similarity'] > 0].sort_values(by='similarity', ascending=False)['TranslatedRecipeName']

    return list(relevant_recipes)

# Function to generate a weekly meal plan -------------------------------------
def generate_meal_plan():
    days = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
    meal_plan = []

    for day in days:
        try:
            # Attempt to select a random index within the valid range
            random_index = random.choice(df.index)
            breakfast_recipe = df.at[random_index, 'TranslatedRecipeName']
            
        except KeyError:
            # Handle the KeyError by choosing a different recipe or providing a default
            breakfast_recipe = 'Default Breakfast Recipe'

        try:
            # Attempt to select a random index within the valid range
            random_index = random.choice(df.index)
            lunch_recipe = df.at[random_index, 'TranslatedRecipeName']
        except KeyError:
            # Handle the KeyError by choosing a different recipe or providing a default
            lunch_recipe = 'Default Lunch Recipe'

        try:
            # Attempt to select a random index within the valid range
            random_index = random.choice(df.index)
            dinner_recipe = df.at[random_index, 'TranslatedRecipeName']
        except KeyError:
            # Handle the KeyError by choosing a different recipe or providing a default
            dinner_recipe = 'Default Dinner Recipe'

        day_meal = {
            'day': day,
            'breakfast': breakfast_recipe,
            'lunch': lunch_recipe,  
            'dinner': dinner_recipe,
        }
        meal_plan.append(day_meal)

    return meal_plan

def get_ingredients_for_recipe(recipe_name):
    recipe_row = df[df['TranslatedRecipeName'] == recipe_name]
    if not recipe_row.empty:
        ingredients_str = recipe_row['TranslatedIngredients'].iloc[0]
        ingredients = ingredients_str.split(', ')
        return ingredients
    else:
        return []

def generate_grocery_list(weekly_meal_plan):
    grocery_list = set()  # Use a set to store unique ingredients

    for day_meal in weekly_meal_plan:
        for meal_type in ['breakfast', 'lunch', 'dinner']:
            recipe_name = day_meal[meal_type]
            ingredients = get_ingredients_for_recipe(recipe_name)
            grocery_list.update(ingredients)

    return list(grocery_list)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/meal_plan', methods=['GET'])
def get_meal_plan():
    meal_plan = generate_meal_plan()
    return jsonify(meal_plan)

@app.route('/api/recommend_recipe', methods=['GET'])
def get_recommended_recipe():
    ingredients = request.args.get('ingredients')
    recommended_recipes = recommend_recipe(ingredients)
    return jsonify(recommended_recipes)

@app.route('/api/generate_grocery_list')
def generate_grocery_list():
    grocery_list = generate_grocery_list(meal_plan)

    # Create a string representation of the grocery list
    grocery_list_content = '\n'.join(grocery_list)

    # Respond with the content
    return grocery_list_content

if __name__ == '__main__':
    app.run(debug=True)