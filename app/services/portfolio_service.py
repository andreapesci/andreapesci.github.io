import json
from pathlib import Path
from typing import List, Dict
from app.models.portfolio_model import Project
from pydantic.tools import parse_obj_as

def load_data():
    file = Path(__file__).parent.parent / 'db' / 'portfolio.json'
    with open(file, 'r') as fin:
        data = json.load(fin)
    return data

def all_projects() -> List[Project]:
    data = load_data()
    portfolio = parse_obj_as(List[Project], data)
    print(portfolio)
    return portfolio


# def top_videos(count: int = 3) -> Portfolio:
#     load_data()
#     return all_videos()[:count]