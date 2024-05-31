import json
from pathlib import Path
from typing import List, Dict
from app.models.blog_model import Post
from pydantic.tools import parse_obj_as

def load_data():
    file = Path(__file__).parent.parent / 'db' / 'blog.json'
    with open(file, 'r') as fin:
        data = json.load(fin)
    return data

def all_blogs() -> List[Post]:
    data = load_data()
    blog = parse_obj_as(List[Post], data)
    print(blog)
    return blog


# def top_videos(count: int = 3) -> Portfolio:
#     load_data()
#     return all_videos()[:count]