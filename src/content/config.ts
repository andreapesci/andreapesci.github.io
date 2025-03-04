import { defineCollection, z } from 'astro:content';

const projectsCollection = defineCollection({
  type: 'data',
  schema: z.object({
    title: z.string(),
    description: z.string(),
    briefDescription: z.string(),
    skills: z.array(z.string()),
    technologies: z.array(z.string()),
    image: z.string(),
    demoUrl: z.string().optional(),
    repositoryUrl: z.string().optional(),
    featured: z.boolean().optional(),
    sections: z.array(
      z.object({
        title: z.string(),
        content: z.string().optional(),
        listItems: z.array(z.string()).optional().default([]),
        image: z.string().optional(),
        videoUrl: z.string().optional()
      })
    ).optional().default([])
  })
});

const aboutCollection = defineCollection({
    type: 'data',
    schema: z.object({
      title: z.string(),
      subtitle: z.string(),
      intro: z.string(),
      heroText: z.string(),
      shortBio: z.string(),
      skills: z.array(z.string()),
      experience: z.array(
        z.object({
          company: z.string(),
          role: z.string(),
          period: z.string(),
          description: z.string()
        })
      ),
      education: z.array(
        z.object({
          institution: z.string(),
          degree: z.string(),
          year: z.string()
        })
      ),
      contacts: z.object({
        email: z.string(),
        github: z.string().optional(),
        linkedin: z.string().optional()
      }),
      featuredImage: z.string().optional()
    })
  });

  console.log(aboutCollection)

export const collections = {
  projects: projectsCollection,
  about: aboutCollection
};
