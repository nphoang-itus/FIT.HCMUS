/* eslint-disable @typescript-eslint/no-explicit-any */

import { toast } from "sonner";

export interface ChatMessage {
  role: "user" | "assistant";
  content: string;
  timestamp?: Date;
}

export interface OllamaRequestBody {
  model: string;
  prompt?: string;
  messages?: {
    role: string;
    content: string;
  }[];
  stream?: boolean;
  options?: Record<string, any>;
}

export interface OllamaResponseMessage {
  model: string;
  created_at: string;
  message: {
    role: string;
    content: string;
  };
}

// Default Ollama API endpoint (assumes Ollama is running locally)
const OLLAMA_API_URL = "http://localhost:11434";

export const getModels = async (): Promise<{id: string, name: string}[]> => {
  try {
    const response = await fetch(`${OLLAMA_API_URL}/api/tags`);
    
    if (!response.ok) {
      throw new Error(`Failed to fetch models: ${response.statusText}`);
    }
    
    const data = await response.json();
    
    // Map the returned models to our format
    return data.models?.map((model: any) => ({
      id: model.name,
      name: model.name
    })) || [];
    
  } catch (error) {
    console.error("Error fetching Ollama models:", error);
    toast.error("Failed to connect to Ollama. Is Ollama running?");
    return []; 
  }
};

export const sendMessage = async (
  message: string, 
  model: string,
  previousMessages: ChatMessage[]
): Promise<string> => {
  try {
    // Map our internal messages to Ollama format
    const ollamaMessages = previousMessages.map(msg => ({
      role: msg.role,
      content: msg.content
    }));
    
    // Add the new message
    ollamaMessages.push({
      role: "user",
      content: message
    });
    
    const requestBody: OllamaRequestBody = {
      model,
      messages: ollamaMessages,
      stream: false
    };
    
    const response = await fetch(`${OLLAMA_API_URL}/api/chat`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(requestBody)
    });
    
    if (!response.ok) {
      throw new Error(`Ollama API error: ${response.statusText}`);
    }
    
    const data: OllamaResponseMessage = await response.json();
    return data.message.content;
    
  } catch (error) {
    console.error("Error sending message to Ollama:", error);
    toast.error("Failed to get a response from Ollama");
    return "Sorry, I encountered an error while processing your request.";
  }
};
