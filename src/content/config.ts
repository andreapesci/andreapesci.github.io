import { defineCollection, z } from 'astro:content';

const projectsCollection = defineCollection({
  type: 'data',
  schema: z.object({
    title: z.string(),
    description: z.string(),
    technologies: z.array(z.string()),
    image: z.string(),
    demoUrl: z.string().optional(),
    repositoryUrl: z.string().optional()
  })
});

export const collections = {
  'projects': projectsCollection
};
